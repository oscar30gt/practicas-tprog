/**
 * @file elemento.cc
 *
 * @authors
 * Hugo García Sánchez (930108)
 * Óscar Grimal Torres (926897)
 */

#include <iostream>
#include <iomanip>
#include <string>

#include "elemento.h"

/** Espacios entre niveles de indentación al imprimir */
#define TAB_SIZE 2

std::ostream &operator<<(std::ostream &os, const Elemento &e)
{
    e.imprimir(os, 0); // Comenzamos con 0 espacios de indentación
    return os;
}

void Elemento::imprimir(std::ostream &os, int indent) const
{
    // Formato: "Nombre [Volumen m3] [Peso kg]"
    os << std::string(indent * TAB_SIZE, ' ') << nombre()
       << " [" << volumen() << " m3] [" << peso() << " kg]"
       << std::endl;
}

Elemento::Elemento(const std::string &nombre, double volumen)
    : _nombre(nombre), _volumen(volumen) {}

std::string Elemento::nombre() const { return _nombre; }
double Elemento::volumen() const { return _volumen; }
