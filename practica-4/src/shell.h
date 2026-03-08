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

/**
 * Clase que representa un shell de comandos. El shell mantiene un directorio raíz y un directorio
 * de trabajo actual, y permite ejecutar comandos para manipular el sistema de archivos.
 */
class Shell
{
    /** Directorio raíz del sistema de archivos. */
    const Directorio _root;
    
public:
    /** Directorio de trabajo actual. Es una pila, pero se implementa 
        como un vector para poder recorrerla con mayor facilidad */
    std::vector<std::string> _cwd;

    /** 
     * AUXILIAR
     * Dado un path en forma de string, lo convierte a un vector de strings.
     * @param path Ruta a convertir. Puede ser absoluta o relativa al directorio de trabajo actual.
     * @returns Vector de strings con los nombres de los directorios en la ruta dada.
     */
    std::vector<std::string> path2Vec(const std::string &path) const;

    /**
     * AUXILIAR
     * Dado un path en forma de vector de strings, resuelve la ruta absoluta correspondiente a esa ruta.
     * @param pathVec Ruta al nodo a obtener. Puede ser absoluta o relativa al directorio de trabajo actual.
     *                Si no se especifica, se resuelve el directorio de trabajo actual.
     * @returns Puntero al nodo correspondiente a la ruta dada, o `nullptr` si no existe ningún nodo con esa ruta.
     */
    std::vector<std::string> resolvePath(std::vector<std::string> pathVec) const;

    /**
     * AUXILIAR
     * Dado un path en forma de vector de strings, devuelve un puntero al directorio correspondiente a esa ruta.
     * @param pathVec Ruta al directorio a obtener. Puede ser absoluta o relativa al directorio de trabajo actual.
     *                Si no se especifica, se resuelve el directorio de trabajo actual.
     * @returns Puntero al directorio correspondiente a la ruta dada, o `nullptr` si no existe ningún directorio con esa ruta.
     */
    INode* getNode(std::vector<std::string> pathVec) const;
    Directorio* getNode() const;

    Shell();
    ~Shell() = default;

    // COMANDOS

    // Imprime el directorio de trabajo actual.
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