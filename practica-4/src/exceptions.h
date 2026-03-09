#include <string>
#include <stdexcept>

#define RED "\033[31m"
#define RESET "\033[0m"

class arbol_ficheros_error : public std::runtime_error
{
public:
    arbol_ficheros_error(const std::string &message) : std::runtime_error(RED + message + RESET) {}
};