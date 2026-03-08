/**
 * @file filesystem.h
 *
 * @authors
 * Hugo García Sánchez (930108)
 * Óscar Grimal Torres (926897)
 */

#pragma once

#include <string>
#include <map>

class Enlace;

/**
 * Un nodo es una entidad que puede ser un directorio o un archivo. Cada nodo tiene
 * un nombre y puede ser referenciado por multiples enlaces.
 * Funciona de manera similar a un inodo en un sistema de ficheros linux.
 */
class INode
{
public:
    /** Tipos de inodos */
    enum INodeType
    {
        Directory,
        File
    };

private:
    /** Numero de enlaces al nodo. */
    unsigned int _nlinks = 0;

    /** Tipo de este nodo. */
    const INodeType _type;

public:
    INode(INodeType type): _type(type) {}
    virtual ~INode() = default;

    /**
     * Obtiene el tamaño ocupado en memoria por el nodo.
     * @returns Tamaño del nodo en bytes.
     */
    virtual size_t size() const = 0;

    constexpr bool isDirectory() const { return _type == Directory; };
    constexpr bool isFile() const { return _type == File; };

    friend class Enlace;
};

/**
 * Un directorio es un nodo que no contiene datos, sino que contiene otros nodos dentro
 * de el (archivos o directorios). Su tamaño es el tamaño total de los nodos que contiene.
 */
class Directorio final : public INode
{
    /** Contenido del directorio. */
    std::map<std::string, Enlace> _children;

public:
    Directorio();
    virtual ~Directorio() = default;

    // El tamaño de un directorio es la suma de los tamaños de sus hijos.
    size_t size() const override;

    /**
     * Obtiene el contenido del directorio.
     * @return Mapa con los nodos contenidos en el directorio con pares <nombre, nodo>.
     */
    std::map<std::string, INode *> getChildren() const;

    /**
     * Crea un nuevo elemento en el directorio. El nuevo elemento es un enlace al nodo dado.
     * @param name Nombre del nuevo elemento. Debe ser unico dentro del directorio.
     * @param node Nodo al que apunta el nuevo enlace.
     * @returns `true` si el elemento se ha creado correctamente, `false` si ya existia un
     * elemento con el mismo nombre y, por tanto, no se ha creado el nuevo elemento.
     */
    bool addEntry(std::string name, INode *node);

    /**
     * Elimina un elemento del directorio. Si no existe el elemento, no se hace nada.
     * @param name Nombre del elemento a eliminar. Debe existir dentro del directorio.
     */
    void removeEntry(std::string name);

    /**
     * Busca un elemento dentro del directorio y devuelve su nodo.
     * @param name Nombre del elemento a buscar. Debe existir dentro del directorio.
     * @returns Puntero al nodo del elemento buscado, o `nullptr` si no existe el elemento.
     */
    INode *find(std::string name) const;
};

/**
 * Un fichero es un nodo que contiene datos. Su tamaño es el tamaño de los datos que contiene.
 */
class Fichero final : public INode
{
    /** Tamaño del fichero en bytes. */
    size_t _size;

public:
    /**
     * @param size Tamaño del fichero en bytes. Debe ser un numero positivo.
     */
    Fichero(size_t size);
    virtual ~Fichero() = default;

    // El tamaño de un fichero es el suyo propio.
    size_t size() const override;
};

/**
 * Un enlace es una referencia a un nodo (directorio o archivo) en el sistema de ficheros.
 * Owner: Directorio padre.
 */
class Enlace
{
    /** Directorio padre: ubicación del enlace */
    Directorio *_parent;

    /** Nodo al que apunta el enlace. */
    INode *_target;

public:
    /**
     * @param name Nombre del enlace. Debe ser unico dentro del directorio padre.
     * @param parent Directorio padre del enlace. No puede ser `nullptr`.
     * @param target inodo al que apunta el enlace. No puede ser `nullptr`.
     */
    Enlace(std::string name, Directorio *parent, INode *target);

    // Sobreescribimos el constructor de copia y de movimiento para mantener
    // el conteo de enlaces correcto.
    Enlace(const Enlace &other);
    Enlace(Enlace &&other);

    ~Enlace();

    // Para facilitar la extraccion de datos, el operador flecha y el operador de desreferencia
    // hacen de forma implicita ...->target... y devuelven el nodo al que apunta el enlace.
    INode *operator->() const;
    INode &operator*() const;
};