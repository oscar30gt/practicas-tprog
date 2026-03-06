/**
 * @file cargas.cc
 *
 * @authors
 * Hugo García Sánchez (930108)
 * Óscar Grimal Torres (926897)
 */

#include "cargas.h"
#include "elemento.h"

Transportable::Transportable(const std::string &nombre, double volumen, double peso)
    : Elemento(nombre, volumen), _peso(peso) {}

Transportable::~Transportable() = default;

double Transportable::peso() const { return _peso; }

Carga::Carga(const std::string &nombre, double volumen, double peso)
    : Elemento(nombre, volumen), Transportable(nombre, volumen, peso) {}

Producto::Producto(const std::string &nombre, double volumen, double peso)
    : Elemento(nombre, volumen), Carga(nombre, volumen, peso) {}

SerVivo::SerVivo(const std::string &nombre, double volumen, double peso)
    : Elemento(nombre, volumen), Transportable(nombre, volumen, peso) {}

Toxico::Toxico(const std::string &nombre, double volumen, double peso)
    : Elemento(nombre, volumen), Transportable(nombre, volumen, peso) {}
