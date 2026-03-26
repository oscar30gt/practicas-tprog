/**
 * @file shell.cc
 *
 * @authors
 * Hugo García Sanchez (930108)
 * Óscar Grimal Torres (926897)
 */

#include <sstream>
#include <vector>
#include <iostream>
#include <format>

#include "shell.h"

#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define RESET "\033[0m"

using namespace std;

// ========================== HELPERS ==========================

// Divide un path en sus componentes, ignorando '/' consecutivos y los '.'.
// Por ejemplo, "///a//b/./c" se dividiria en ["a", "b", "c"].
void splitPath(const std::string &path, std::vector<std::string> &out)
{
    out.clear();
    std::istringstream iss(path);
    for (std::string tok; std::getline(iss, tok, '/');)
        if (!tok.empty() && tok != ".")
            out.push_back(tok);
}

// ======================== CONSTRUCTOR ========================

// El constructor inicializa la raiz y la ruta activa con el directorio raiz
Shell::Shell() : _cwdStack()
{
    // Inicialmente, el sistema de archivos solo contiene el directorio raíz.
    // Para mantener vivo el inodo del directorio raíz, el shell mantiene un link a el.
    _cwdStack.push_back({"/", Enlace(new Directorio())});
}

// ===================== METODOS INTERNOS ======================

Shell::str_vec Shell::resolvePath(const std::string &path) const
{
    str_vec tokens;
    splitPath(path, tokens);

    // Si comienza por '/', partimos de la raiz, si no, del CWD actual.
    str_vec res = {};
    if (!path.starts_with('/'))
        for (size_t i = 1; i < _cwdStack.size(); i++)
            res.push_back(_cwdStack[i].first);

    // Procesamos cada parte del path.
    for (const auto &part : tokens)
    {
        if (part == "..")
        {
            if (res.empty())
                throw illegal_action_error("path resolution", "Cannot go above root.");
            res.pop_back();
        }
        else
        {
            res.push_back(part);
        }
    }
    return res;
}

INode *Shell::getNode(const str_vec &pathVec) const
{
    // Siempre empezamos desde la raiz, 
    // pues se nos garantiza que el pathVec es absoluto.
    INode *curr = _cwdStack.front().second.operator->();

    for (auto &part : pathVec)
    {
        // Antes de navegar al siguiente nodo, comprobamos que el nodo actual es un directorio
        // Si no, no podemos navegar, por lo que lo que haya mas alla no existe.
        if (!curr->isDirectory())
            return nullptr;

        curr = static_cast<Directorio *>(curr)->find(part);
        if (!curr)
            return nullptr;

        // En la ultima iteracion, curr puede ser cualquier tipo de inodo, 
        // ya que puede ser la ruta a un fichero y no a un directorio.
    }
    return curr;
}

// Sobrecarga de `getNode` para obtener el nodo del cwd
Directorio *Shell::getNode() const
{
    // El ultimo elemento de la pila de referencias es nuestro CWD
    return static_cast<Directorio *>(_cwdStack.back().second.operator->());
}

// ========================== COMANDOS =========================

std::string Shell::pwd() const
{
    // Root se representa unicamente con '/'
    if (_cwdStack.size() == 1)
        return "/";

    std::string output = "";
    for (size_t i = 1; i < _cwdStack.size(); i++)
        output += "/" + _cwdStack[i].first;

    return output;
}

std::string Shell::ls() const
{
    std::string output = "";
    auto currentDir = getNode();

    for (const auto &[name, node] : currentDir->getChildren())
    {
        output += node->isDirectory() ? YELLOW : CYAN; // Color segun tipo de item
        output += name + "\n";
    }
    return output + RESET;
}

std::string Shell::du() const
{
    std::string output = "NAME            SIZE\n"; // Encabezado de la tabla
    auto currentDir = getNode();

    for (const auto &[name, node] : currentDir->getChildren())
    {
        output += node->isDirectory() ? YELLOW : CYAN; // Color segun tipo de item
        output += std::format("{:<16}{}B\n", name, node->size());
    }
    return output + RESET;
}

void Shell::vi(const std::string &name, int size)
{
    // Validamos el nombre del fichero a crear o modificar
    if (name.contains('/') || name == "." || name == "..")
        throw bad_identifier_error("vi", name);

    auto currentDir = getNode();
    INode *child = currentDir->find(name); // Comprobamos si el nodo ya existe

    if (!child)
        currentDir->addEntry(name, new Fichero(size));
    else if (child->isFile())
        static_cast<Fichero *>(child)->setSize(size);
    else
        throw invalid_type_error("vi", name, "file");
}

void Shell::mkdir(const std::string &name)
{
    // Validamos el nombre del nuevo directorio
    if (name.contains('/') || name == "." || name == "..")
        throw bad_identifier_error("mkdir", name);

    auto currentDir = getNode();
    if (currentDir->find(name))
        throw already_exists_error("mkdir", name);

    currentDir->addEntry(name, new Directorio());
}

void Shell::cd(const std::string &path) {
    // Nuevo path absoluto
    auto names = resolvePath(path);
    
    // Nuevo stack inicializado con la raiz.
    std::vector<named_entry> nwdStack;
    nwdStack.push_back(_cwdStack.front());
    
    // Navegamos para llenar la pila de navegacion
    for (const auto& name : names) {
        // El nodo actual es el ultimo de nuestra nueva pila
        Directorio* curr = static_cast<Directorio*>(nwdStack.back().second.operator->());
        INode* next = curr->find(name);
        
        // Validacion fisica de que el directorio existe
        if (!next) 
            throw path_not_found_error("cd", name);
        if (!next->isDirectory())
            throw invalid_type_error("cd", name, "directory");
            
        // Añadimos a la pila. Esto incrementa nlinks automáticamente.
        nwdStack.push_back({name, Enlace(next)});
    }

    // Intercambiamos la pila de navegacion actual por la nueva.
    _cwdStack = std::move(nwdStack);
}

void Shell::ln(const std::string &path, const std::string &name)
{
    // Validamos el nombre del enlace a crear
    if (name.contains('/'))
        throw bad_identifier_error("ln", name);

    // Nodo al que lleva el enlace a crear
    auto targetPathVec = resolvePath(path);
    auto targetNode = getNode(targetPathVec);

    if (!targetNode)
        throw path_not_found_error("ln", path);

    auto currentDir = getNode();
    if (currentDir->find(name)) 
        throw already_exists_error("ln", name);

    if (targetNode->contains(currentDir))
        throw illegal_action_error("ln", "This link would create a circular reference in the directory tree.");

    currentDir->addEntry(name, targetNode);
}

std::string Shell::stat(const std::string &path) const
{
    auto pathVec = resolvePath(path);
    auto node = getNode(pathVec);

    if (!node)
        throw path_not_found_error("stat", path);

    return std::to_string(node->size()) + " Bytes";
}

void Shell::rm(const std::string &path)
{
    auto pathVec = resolvePath(path);
    if (pathVec.empty())
        throw illegal_action_error("rm", "Cannot remove root directory.");

    // Obtenemos el directorio padre del nodo a eliminar
    std::string name = pathVec.back();
    pathVec.pop_back();
    INode *parentNode = getNode(pathVec);
    if (!parentNode || !parentNode->isDirectory())
        throw path_not_found_error("rm", path);

    // Si el nodo esta en _cwdStack, nlinks seguira > 0 y no se borrara fisicamente hasta que no se salga de el.
    static_cast<Directorio *>(parentNode)->removeEntry(name);
}