/**
 * @file exceptions.h
 *
 * @authors
 * Hugo García Sánchez (930108)
 * Óscar Grimal Torres (926897)
 */

#include <string>
#include <stdexcept>

#define RED "\033[31m"
#define RESET "\033[0m"

/**
 * Tipo de excepcion lanzada por el shell en caso de error con el sistema de ficheros.
 * Hereda de `std::runtime_error` y simplemente colorea el mensaje de error en rojo.
 */
class arbol_ficheros_error : public std::runtime_error
{
public:
    arbol_ficheros_error(const std::string &source, const std::string &message)
        : std::runtime_error(RED + source + ": " + message + RESET) {}
};

// ========================== EXCEPCIONES ESPECIFICAS ==========================

/**
 * Excepcion lanzada cuando se intenta acceder a un path que no existe, ya sea para lectura o escritura.
 * El mensaje de error incluye el path que se ha intentado acceder.
 */
class path_not_found_error final : public arbol_ficheros_error
{
public:
    path_not_found_error(const std::string &source, const std::string &path)
        : arbol_ficheros_error(source, "'" + path + "' does not exist.") {}
};

/**
 * Excepcion lanzada cuando se intenta crear un item (fichero o directorio) con un nombre que ya existe en el directorio actual.
 * El mensaje de error incluye el nombre del item que se ha intentado crear.
 */
class already_exists_error final : public arbol_ficheros_error
{
public:
    already_exists_error(const std::string &source, const std::string &name)
        : arbol_ficheros_error(source, "Error: '" + name + "' already exists in this directory.") {}
};

/**
 * Excepcion lanzada cuando se intenta acceder a un item (fichero o directorio) con un tipo diferente al esperado.
 * Por ejemplo, intentar acceder a un fichero como si fuera un directorio o viceversa.
 */
class invalid_type_error final : public arbol_ficheros_error
{
public:
    invalid_type_error(const std::string &source, const std::string &name, const std::string &expected)
        : arbol_ficheros_error(source, "'" + name + "' is not a " + expected + ".") {}
};

/**
 * Excepcion lanzada cuando se intenta crear un item (fichero o directorio) con un nombre no válido, como por ejemplo un nombre que contiene '/' o es igual a '.' o '..'.
 * El mensaje de error incluye el nombre del item que se ha intentado crear.
 */
class bad_identifier_error final : public arbol_ficheros_error
{
public:
    bad_identifier_error(const std::string &source, const std::string &name)
        : arbol_ficheros_error(source, "Name '" + name + "' is not valid.") {}
};

/**
 * Excepcion lanzada cuando se intenta realizar una accion no permitida en el sistema de ficheros,
 * como por ejemplo intentar eliminar el directorio raiz.
 */
class illegal_action_error final : public arbol_ficheros_error
{
public:
    illegal_action_error(const std::string &source, const std::string &message)
        : arbol_ficheros_error(source, "Illegal action: " + message) {}
};