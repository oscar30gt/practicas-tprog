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

Shell::Shell() : _root(), _cwd() {} // <- cwd vacio = raiz

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

Directorio *Shell::getDir(std::vector<std::string> path) const
{
    Directorio *dir = const_cast<Directorio *>(&_root);

    for (const auto &name : path)
    {
        if (name == "/")
            continue;

        auto child = dir->find(name);
        if (!child || !child->isDirectory())
            return nullptr;

        dir = static_cast<Directorio *>(child);
    }

    return dir;
}

// =========================== COMANDOS ===========================

std::string Shell::pwd() const //[DONE]:
{
    std::string output;
    for (const auto &dir : _cwd)
        output += "/" + dir;

    return output.empty() ? "/" : output;
}

std::string Shell::ls() const //[DONE]:
{
    std::string output = _cwd.empty() ? "" : "\033[34m.\n..\n\033[0m";

    auto dir = getDir(_cwd);
    for (const auto &[name, node] : dir->getChildren())
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
    return "";
}

void Shell::vi(const std::string &name, int size)
{
}

void Shell::mkdir(const std::string &name)
{
    std::vector<std::string> pathVec = path2Vec(name);
    Directorio *currentDir = getDir(_cwd);

    for (auto part : pathVec)
    {
        if (part == ".")
            continue;

        if (part == "/")
        {
            currentDir = const_cast<Directorio *>(&_root);
            continue;
        }

        if (part == "..")
        {
            if (_cwd.empty())
                throw std::runtime_error("DIR NO EXISTE");
            _cwd.pop_back();
            currentDir = getDir(_cwd);
            continue;
        }

        auto child = currentDir->find(part);
        if (child)
        {
            if (!child->isDirectory())
                throw std::runtime_error("YA EXISTE");

            currentDir = static_cast<Directorio *>(child);
        }
        else
        {
            Directorio *newDir = new Directorio();
            currentDir->addEntry(part, newDir);
            currentDir = newDir;
        }
    }
}

void Shell::cd(const std::string &path)
{
    std::vector<std::string> pathVec = path2Vec(path);

    for (const auto &dir : pathVec)
    {
        if (dir == ".")
            continue;

        if (dir == "/")
        {
            _cwd.clear();
            continue;
        }

        if (dir == "..")
        {
            if (_cwd.empty())
                throw std::runtime_error("DIR NO EXISTE");
            _cwd.pop_back();
            continue;
        }

        auto child = getDir(_cwd)->find(dir);
        if (!child || !child->isDirectory())
            throw std::runtime_error("DIR NO EXISTE");

        _cwd.push_back(dir);
    }
}

void Shell::ln(const std::string &path, const std::string &name)
{
}

std::string Shell::stat(const std::string &path) const
{
    return "";
}

void Shell::rm(const std::string &path)
{
}