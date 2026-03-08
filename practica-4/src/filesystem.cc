/**
 * @file filesystem.cc
 *
 * @authors
 * Hugo García Sánchez (930108)
 * Óscar Grimal Torres (926897)
 */

#include "filesystem.h"

// =========================== INode ===========================

INode::INode() : _nlinks(0) {}

// =========================== Directorio ===========================

Directorio::Directorio() : INode() {}

size_t Directorio::size() const
{
    size_t total_size = 0;
    for (const auto &[_, link] : _children)
        total_size += link->size();
    return total_size;
}

bool Directorio::addEntry(std::string name, INode *node)
{
    if (_children.contains(name))
        return false;
    _children.emplace(name, Enlace(name, this, node));
    return true;
}

void Directorio::removeEntry(std::string name)
{
    _children.erase(name);
}

INode *Directorio::find(std::string name) const
{
    auto iterator = _children.find(name);
    if (iterator == _children.end())
        return nullptr; // No existe el elemento

    // Devolvemos el puntero al nodo al que apunta el enlace
    return iterator->second.operator->();
}

// =========================== Fichero ===========================

Fichero::Fichero(size_t size) : INode(), _size(size) {}
size_t Fichero::size() const
{
    return _size;
}

// =========================== Enlace ===========================

Enlace::Enlace(const Enlace &other)
    : _parent(other._parent), _target(other._target)
{
    _target->_nlinks++;
}

Enlace::Enlace(Enlace &&other)
    : _parent(other._parent), _target(other._target)
{
    other._target = nullptr;
}

Enlace::Enlace(std::string name, Directorio *parent, INode *target)
    : _parent(parent), _target(target)
{
    target->_nlinks++;
}

Enlace::~Enlace()
{
    if (_target != nullptr && --_target->_nlinks == 0)
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