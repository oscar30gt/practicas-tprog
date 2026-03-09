/**
 * @file shell.cc
 *
 * @authors
 * Hugo García Sánchez (930108)
 * Óscar Grimal Torres (926897)
 */

#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>

#include "shell.h"

#define BLUE "\033[34m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define RESET "\033[0m"

Shell::Shell() : _root(), _cwd() {}

// ========================== HELPERS ==========================

std::vector<std::string> Shell::resolvePath(const std::string &path) const
{
    std::vector<std::string> pathVec;
    std::istringstream iss(path);
    for (std::string tok; std::getline(iss, tok, '/');)
        if (!tok.empty())
            pathVec.push_back(tok);

    // Punto de partida: path vacio para root o cwd si es relativo.
    std::vector<std::string> normalized = path.starts_with('/')
                                              ? std::vector<std::string>()
                                              : _cwd;

    // Normalizamos el path, resolviendo los "." y ".." y navegando entre directorios.
    for (const auto &part : pathVec)
    {
        if (part == "..")
        {
            if (normalized.size() <= 1) // No podemos subir mas alla del root.
                throw arbol_ficheros_error("Cannot go above root directory");
            normalized.pop_back();
        }
        else if (part != ".") // Ignoramos los "." porque no afectan a la ruta.
        {
            normalized.push_back(part);
        }
    }

    return normalized;
}

INode *Shell::getNode(std::vector<std::string> pathVec) const
{
    // Siempre se nos pide resolver un path absoluto, asi que partimos desde root.
    INode *curr = const_cast<Directorio *>(&_root);

    for (size_t i = 0; i < pathVec.size(); i++)
    {
        // Antes de buscar el siguiente nombre, comprobamos que el nodo actual es un directorio.
        if (!curr->isDirectory())
            return nullptr;

        curr = static_cast<Directorio *>(curr)->find(pathVec[i]);

        // Si no existe el nombre, la ruta es invalida
        if (!curr)
            return nullptr;
    }

    return curr;
}

Directorio *Shell::getNode() const { return static_cast<Directorio *>(getNode(_cwd)); }

// =========================== COMANDOS ===========================

std::string Shell::pwd() const
{
    std::string output;
    for (const auto &dir : _cwd)
    {
        if (dir != "/")
            output += "/" + dir;
    }

    return output.empty() ? "/" : output;
}

std::string Shell::ls() const
{
    std::string output = _cwd.empty() ? "" : (BLUE + std::string(".\n..\n") + RESET);

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
    // El nombre del fichero no puede contener el caracter '/' porque es el separador de directorios.
    if (name.contains('/'))
        throw arbol_ficheros_error("Bad filename");

    // Ver si ya existe un nodo con el mismo nombre en el directorio actual.
    auto currentDir = getNode();
    auto child = currentDir->find(name);

    // Si no existe, crear un nuevo fichero con el tamaño dado.
    if (!child)
    {
        Fichero *newFile = new Fichero(size);
        currentDir->addEntry(name, newFile);
        return;
    }

    // Si ya existe el fichero, cambiar su tamaño al dado.
    if (child->isFile())
    {
        static_cast<Fichero *>(child)->setSize(size);
        return;
    }

    throw arbol_ficheros_error("Cannot change size. '" + name + "' is a directory");
}

void Shell::mkdir(const std::string &name)
{
    // El nombre del directorio no puede contener el caracter '/' porque es el separador de directorios.
    if (name.contains('/'))
        throw arbol_ficheros_error("Bad dirname");

    // Ver si ya existe un nodo con el mismo nombre en el directorio actual.
    auto currentDir = getNode();
    auto child = currentDir->find(name);

    if (!child)
    {
        Directorio *newDir = new Directorio();
        currentDir->addEntry(name, newDir);
        return;
    }

    throw arbol_ficheros_error("Directory with name '" + name + "' already exists");
}

void Shell::cd(const std::string &path)
{
    auto nwd = resolvePath(path);
    auto dir = getNode(nwd);

    if (!dir)
        throw arbol_ficheros_error("Directory '" + path + "' does not exist");

    if (!dir->isDirectory())
        throw arbol_ficheros_error("'" + path + "' is not a directory");

    _cwd = nwd;
}

void Shell::ln(const std::string &path, const std::string &name)
{
    // El nombre del enlace no puede contener el caracter '/' porque es el separador de directorios.
    if (name.contains('/'))
        throw arbol_ficheros_error("Bad link name");

    // Nodo al que apunta el enlace.
    auto targetPathVec = resolvePath(path);
    auto targetNode = getNode(targetPathVec);

    if (!targetNode)
        throw arbol_ficheros_error("'" + path + "' does not exist");

    // Comprobamos que no exista un nodo con el mismo nombre en el directorio actual.
    auto currentDir = getNode();
    auto child = currentDir->find(name);

    if (child)
        throw arbol_ficheros_error("Item with name '" + name + "' already exists");

    currentDir->addEntry(name, targetNode);
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
    std::string filename = pathVec.back();

    // Obtenemos el directorio padre del nodo a eliminar.
    pathVec.pop_back();
    auto parent = getNode(pathVec);

    static_cast<Directorio *>(parent)->removeEntry(filename);
}