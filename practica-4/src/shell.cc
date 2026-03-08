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

Shell::Shell() : _root(), _cwd({"/"}) {}

// ========================== AUXILIARES ==========================

std::vector<std::string> Shell::path2Vec(const std::string &path) const
{
    std::vector<std::string> vec;

    if (path.starts_with('/'))
        vec.push_back("/");

    std::istringstream iss(path);
    for (std::string tok; std::getline(iss, tok, '/');)
        if (!tok.empty())
            vec.push_back(tok);

    return vec;
}

std::vector<std::string> Shell::resolvePath(std::vector<std::string> pathVec) const
{
    std::vector<std::string> normalized = _cwd;
    
    // Primero normalizamos el path, resolviendo los "." y ".." y comprobando
    // que cada parte del path existe y es un directorio.
    for (const auto &part : pathVec)
    {
        if (part == "/")
        {
            normalized.clear();
            normalized.push_back("/");
        }
        else if (part == "..")
        {
            if (normalized.size() <= 1) // No podemos subir mas alla del root.
                throw std::runtime_error("NO EXISTE");
            normalized.pop_back();
        }
        else if (part != ".")
        {
            normalized.push_back(part);
        }
    }

    return normalized;
}

INode *Shell::getNode(std::vector<std::string> pathVec) const
{
    // Si el path es correcto, obtenemos el directorio correspondiente al path normalizado.
    Directorio *dir = const_cast<Directorio *>(&_root);
    auto normalized = resolvePath(pathVec);

    if (normalized.size() <= 1)
        return dir;

    for (size_t i = 1; i < normalized.size() - 1; i++)
    {
        const auto &part = normalized[i];
        if (!dir->isDirectory())
            return nullptr;

        INode *next = dir->find(part);
        if (!next || !next->isDirectory())
            return nullptr;

        dir = static_cast<Directorio *>(next);
    }

    return dir->find(normalized.back());
}

Directorio *Shell::getNode() const
{
    return static_cast<Directorio *>(getNode({}));
}

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
    std::string output = _cwd.size() <= 1 ? "" : "\033[34m.\n..\n\033[0m";

    auto currentDir = getNode();
    for (const auto &[name, node] : currentDir->getChildren())
    {
        if (node->isDirectory())
            output += "\033[33m" + name + "\n\033[0m";
        else
            output += "\033[36m" + name + "\n\033[0m";
    }

    return output;
}

std::string Shell::du() const
{
    std::string output;

    auto currentDir = getNode();
    for (const auto &[name, node] : currentDir->getChildren())
        output += name + " " + std::to_string(node->size()) + " bytes\n";

    return output;
}

void Shell::vi(const std::string &name, int size)
{
    auto currentDir = getNode();
    auto child = currentDir->find(name);

    if (child && !child->isFile())
    {
        static_cast<Fichero *>(child)->setSize(size);
    }
    else if (!child)
    {
        Fichero *newFile = new Fichero(size);
        currentDir->addEntry(name, newFile);
    }
    else
    {
        throw std::runtime_error("YA EXISTE Y NO ES UN FICHERO");
    }
}

void Shell::mkdir(const std::string &name)
{
    auto currentDir = getNode();
    auto child = currentDir->find(name);

    if (child)
        throw std::runtime_error("YA EXISTE");

    Directorio *newDir = new Directorio();
    currentDir->addEntry(name, newDir);
}

void Shell::cd(const std::string &path)
{
    auto pathVec = path2Vec(path);
    auto nwd = resolvePath(pathVec);
    auto dir = getNode(nwd);

    if (!dir || !dir->isDirectory())
        throw std::runtime_error("NO EXISTE");

    _cwd = nwd;
}

void Shell::ln(const std::string &path, const std::string &name)
{
    auto targetPathVec = path2Vec(path);
    auto targetNode = getNode(targetPathVec);

    if (!targetNode)
        throw std::runtime_error("NO EXISTE");

    auto currentDir = getNode();
    auto child = currentDir->find(name);

    if (child)
        throw std::runtime_error("YA EXISTE");

    currentDir->addEntry(name, targetNode);
}

std::string Shell::stat(const std::string &path) const
{
    auto pathVec = path2Vec(path);
    auto node = getNode(pathVec);

    if (!node)
        throw std::runtime_error("NO EXISTE");

    return std::to_string(node->size()) + " bytes";
}

void Shell::rm(const std::string &path)
{
    auto pathVec = path2Vec(path);
    std::string filename = pathVec.back();

    // Obtenemos el directorio padre del nodo a eliminar.
    pathVec.push_back(".."); 
    auto parent = getNode(pathVec);

    static_cast<Directorio *>(parent)->removeEntry(filename);
}