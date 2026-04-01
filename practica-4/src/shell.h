/**
 * @file shell.h
 *
 * @authors
 * Hugo García Sánchez (930108)
 * Óscar Grimal Torres (926897)
 */

#pragma once

#include <string>
#include <vector>

#include "filesystem.h"
#include "exceptions.h"

/**
 * Clase que representa un shell de comandos. El shell mantiene un directorio raíz y un directorio
 * de trabajo actual, y permite ejecutar comandos para manipular el sistema de archivos.
 */
class Shell
{
    // Vector de strings
    using str_vec = std::vector<std::string>;

    // Par nombre-enlace
    using named_entry = std::pair<std::string, Enlace>;

    /** 
     * RUTA ACTIVA (CWD): Secuencia de referencias a directorios.
     * Las referencias son enlaces como los que se encuentran en los directorios,
     * pero sin estar asociados a ninguno. Esto mantiene vivo el inodo
     * aunque borremos el directorio que lo contiene.
     * Cada enlace va asociado a un nombre.
     */
    std::vector<named_entry> _cwdStack;

    /**
     * Dado un path absoluto o relativo, lo normaliza en base al cwd.
     * @param path Path a resolver. Puede ser absoluto (comienza con '/') o relativo al directorio de trabajo actual.
     * @param[out] out Vector de strings donde se guardara el resultado de la resolucion del path. El vector resultante representa un path absoluto.
     * @throws `arbol_ficheros_error` Si el path es imposible de resolver (sube por encima del directorio raiz).
     */
    void resolvePath(const std::string &path, str_vec &out) const;

    /**
     * Dado un path absoluto en forma de vector de strings, obtiene el nodo al que apunta.
     * @param pathVec Path absoluto en forma de vector de strings. Si no se especifica, cwd.
     * @returns Puntero al nodo al que apunta el path, o `nullptr` si el path no existe.
     */
    INode *getNode(const str_vec &pathVec) const;
    Directorio *getNode() const;

public:
    Shell();
    ~Shell() = default;

    // ================== COMANDOS ==================

    // Devuelve el path absoluto del directorio de trabajo actual.
    std::string pwd() const;

    // Lista el contenido del directorio de trabajo actual.
    std::string ls() const;

    // Devuelve una lista con el nombre y tamaño de cada elemento del directorio de trabajo actual.
    std::string du() const;

    // Cambia el tamaño del fichero `name` a `size` bytes. Si no existe, lo crea.
    void vi(const std::string &name, int size);

    // Crea un nuevo directorio con el nombre dado dentro del directorio de trabajo actual.
    void mkdir(const std::string &name);

    // Cambia el directorio de trabajo actual al directorio especificado por `path`, que puede ser relativo o absoluto.
    void cd(const std::string &path);

    // Crea un enlace con nombre `name` al nodo especificado por `path`, que puede ser relativo o absoluto.
    void ln(const std::string &path, const std::string &name);

    // Devuelve el tamaño del nodo `path`, que puede ser relativo o absoluto.
    std::string stat(const std::string &path) const;

    // Elimina el nodo especificado por `path`, que puede ser relativo o absoluto.
    void rm(const std::string &path);
};