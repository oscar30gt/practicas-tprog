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
#include <algorithm>

#include "shell.h"

#define BLUE "\033[34m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define RESET "\033[0m"

// ========================== HELPERS ==========================

// Divide un path en sus componentes, ignorando '/' consecutivos y los '.'.
void tokenizePath(const std::string &path, std::vector<std::string> &out)
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
    _cwdStack.push_back({"/", Enlace("root", new Directorio())});
}

// ===================== METODOS INTERNOS ======================

Shell::str_vec Shell::resolvePath(const std::string &path) const
{
    str_vec tokens;
    tokenizePath(path, tokens);

    // Si comienza por '/', partimos de la raiz, si no, del CWD actual
    str_vec res = {};
    if (!path.starts_with('/'))
        for (size_t i = 1; i < _cwdStack.size(); i++)
            res.push_back(_cwdStack[i].first);

    for (const auto &part : tokens)
    {
        if (part == "..")
        {
            if (res.empty())
                throw arbol_ficheros_error("An error occurred while resolving the path: cannot go above root");
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
    INode *curr = _cwdStack.front().second.operator->(); // Partimos de la raiz o del CWD actual, segun el caso

    for (auto &part : pathVec)
    {
        // Antes de navegar al siguiente nodo, comprobamos que el nodo actual es un directorio
        if (!curr->isDirectory())
            return nullptr;

        curr = static_cast<Directorio *>(curr)->find(part);
        if (!curr)
            return nullptr;
    }
    return curr;
}

Directorio *Shell::getNode() const
{
    // El último elemento de la pila de referencias es nuestro CWD
    return static_cast<Directorio *>(_cwdStack.back().second.operator->());
}

// ========================== COMANDOS =========================

std::string Shell::pwd() const
{
    if (_cwdStack.size() == 1)
        return "/";

    std::string output = "";
    for (size_t i = 1; i < _cwdStack.size(); i++)
        output += "/" + _cwdStack[i].first;

    return output;
}

std::string Shell::ls() const
{
    std::string output = _cwdStack.size() == 1 ? "" : (BLUE + std::string(".\n..\n") + RESET);
    auto currentDir = getNode();

    for (const auto &[name, node] : currentDir->getChildren())
    {
        output += node->isDirectory() ? YELLOW : CYAN;
        output += name + "\n";
    }
    return output + RESET;
}

std::string Shell::du() const
{
    std::string output = "NAME            SIZE\n";
    auto currentDir = getNode();

    for (const auto &[name, node] : currentDir->getChildren())
    {
        output += node->isDirectory() ? YELLOW : CYAN;
        output += std::format("{:<16}{}B\n", name, node->size());
    }
    return output + RESET;
}

void Shell::vi(const std::string &name, int size)
{
    if (name.contains('/'))
        throw arbol_ficheros_error("Bad filename");

    auto currentDir = getNode();
    INode *child = currentDir->find(name);

    if (!child)
        currentDir->addEntry(name, new Fichero(size));
    else if (child->isFile())
        static_cast<Fichero *>(child)->setSize(size);
    else
        throw arbol_ficheros_error("'" + name + "' is a directory");
}

void Shell::mkdir(const std::string &name)
{
    if (name.contains('/'))
        throw arbol_ficheros_error("Bad dirname");

    auto currentDir = getNode();
    if (!currentDir->addEntry(name, new Directorio()))
        throw arbol_ficheros_error("Node '" + name + "' already exists");
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
        
        // Validación fisica
        if (!next) 
            throw arbol_ficheros_error("cd: " + name + ": No such directory");
        if (!next->isDirectory())
            throw arbol_ficheros_error("cd: " + name + ": Not a directory");
            
        // Añadimos a la pila. Esto incrementa nlinks automáticamente.
        nwdStack.push_back({name, Enlace(name, next)});
    }

    // Intercambiamos la pila de navegacion actual por la nueva.
    _cwdStack = std::move(nwdStack);
}

void Shell::ln(const std::string &path, const std::string &name)
{
    if (name.contains('/'))
        throw arbol_ficheros_error("Bad link name");

    auto targetPathVec = resolvePath(path);
    auto targetNode = getNode(targetPathVec);

    if (!targetNode)
        throw arbol_ficheros_error("Target '" + path + "' does not exist");

    auto currentDir = getNode();
    if (!currentDir->addEntry(name, targetNode))
        throw arbol_ficheros_error("Item '" + name + "' already exists");
}

std::string Shell::stat(const std::string &path) const
{
    auto pathVec = resolvePath(path);
    auto node = getNode(pathVec);

    if (!node)
        throw arbol_ficheros_error("'" + path + "' does not exist");

    return std::to_string(node->size()) + " Bytes";
}

void Shell::rm(const std::string &path)
{
    auto pathVec = resolvePath(path);
    if (pathVec.empty())
        throw arbol_ficheros_error("Cannot remove root");

    std::string name = pathVec.back();
    pathVec.pop_back();

    INode *parentNode = getNode(pathVec);
    if (!parentNode || !parentNode->isDirectory())
        throw arbol_ficheros_error("Parent not found");

    // Si el nodo esta en _cwdStack, nlinks seguira > 0 y no se borrara fisicamente
    static_cast<Directorio *>(parentNode)->removeEntry(name);
}