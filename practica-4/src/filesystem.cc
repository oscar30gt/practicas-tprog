/**
 * @file filesystem.cc
 *
 * @authors
 * Hugo García Sánchez (930108)
 * Óscar Grimal Torres (926897)
 */

#include "filesystem.h"

// =========================== Directorio ===========================

Directorio::Directorio() : INode(INodeType::Directory) {}

size_t Directorio::size() const
{
    size_t total_size = 0;
    for (const auto &[_, link] : _children)
        total_size += link->size();
    return total_size;
}

bool Directorio::contains(INode *other) const
{
    if (this == other) // Early return para evitar recorrer todo el arbol.
        return true;

    for (const auto &[_, link] : _children)
        if (link->contains(other))
            return true;
    return false;
}

std::map<std::string, INode *> Directorio::getChildren() const
{
    // Convertimos enlaces a nodos para facilitar su uso
    std::map<std::string, INode *> children;
    for (const auto &[name, link] : _children)
        children[name] = link.operator->();
    return children;
}

bool Directorio::addEntry(const std::string &name, INode *node)
{
    if (_children.contains(name))
        return false;
    _children.emplace(name, Enlace(node));
    return true;
}

void Directorio::removeEntry(const std::string &name)
{
    _children.erase(name);
}

INode *Directorio::find(const std::string &name) const
{
    auto iterator = _children.find(name);
    if (iterator == _children.end())
        return nullptr; // No existe el elemento

    // Devolvemos el puntero al nodo al que apunta el enlace
    return iterator->second.operator->();
}

// =========================== Fichero ===========================

Fichero::Fichero(size_t size) : INode(INodeType::File), _size(size) {}
size_t Fichero::size() const
{
    return _size;
}

void Fichero::setSize(size_t newSize)
{
    _size = newSize;
}

bool Fichero::contains(INode *other) const
{
    // Un fichero solo contiene a si mismo
    return this == other;
}

// =========================== Enlace ===========================

Enlace::Enlace(INode *target) 
    : _target(target) 
{
    if (_target) {
        _target->_nlinks++;
    }
}

Enlace::Enlace(const Enlace &other) : Enlace(other._target) { }
Enlace::Enlace(Enlace &&other) : _target(other._target) { other._target = nullptr; }

Enlace::~Enlace()
{ 
    if (_target && --_target->_nlinks == 0)
        delete _target;
}

INode *Enlace::operator->() const
{
    return _target;
}

INode &Enlace::operator*() const
{
    return *_target;
}