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
 * Hereda de `std::runtime_error` y formatea el mensaje de error para incluir el origen del error
 * y detalles del mismo, en color rojo para destacar el error en la salida.
 */
class arbol_ficheros_error : public std::runtime_error
{
public:
    /**
     * @param source Que ha generado el error, por ejemplo el comando o funcion que se ha intentado ejecutar.
     * @param message Detalles del error que se ha producido.
     */
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
    /**
     * @param source Que ha generado el error, por ejemplo el comando o funcion que se ha intentado ejecutar.
     * @param path Ruta a la que se ha intentado acceder y que no existe en el sistema de ficheros.
     */
    path_not_found_error(const std::string &source, const std::string &path)
        : arbol_ficheros_error(source, "'" + path + "' does not exist.") {}
};

/**
 * Excepcion lanzada cuando se intenta crear un item (fichero o directorio) con un nombre que ya existe 
 * en el directorio actual. El mensaje de error incluye el nombre del item que se ha intentado crear.
 */
class already_exists_error final : public arbol_ficheros_error
{
public:
    /**
     * @param source Que ha generado el error, por ejemplo el comando o funcion que se ha intentado ejecutar.
     * @param name Nombre del item que se ha intentado crear y que ya existe en el directorio actual.
     */
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
    /**
     * @param source Que ha generado el error, por ejemplo el comando o funcion que se ha intentado ejecutar.
     * @param name Nombre del item al que se ha intentado acceder.
     * @param expected Tipo de item que se esperaba encontrar (por ejemplo "file" o "directory").
     */
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
    /**
     * @param source Que ha generado el error, por ejemplo el comando o funcion que se ha intentado ejecutar.
     * @param name Nombre del item que se ha intentado crear y que no es válido para el sistema de ficheros.
     */
    bad_identifier_error(const std::string &source, const std::string &name)
        : arbol_ficheros_error(source, "Name '" + name + "' is not valid. Identifiers cannot contain slashes or be '.' or '..'.") {}
};

/**
 * Excepcion lanzada cuando se intenta realizar una accion no permitida en el sistema de ficheros,
 * como por ejemplo intentar eliminar el directorio raiz.
 */
class illegal_action_error final : public arbol_ficheros_error
{
public:
    /**
     * @param source Que ha generado el error, por ejemplo el comando o funcion que se ha intentado ejecutar.
     * @param message Detalles de la accion no permitida que se ha intentado realizar.
     */
    illegal_action_error(const std::string &source, const std::string &message)
        : arbol_ficheros_error(source, "Illegal action: " + message) {}
};