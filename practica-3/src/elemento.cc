#include "elemento.h"
#include <iostream>

#define TAB_SIZE 2

ostream &operator<<(ostream &os, const Elemento &e)
{
    e.imprimir(os, 0); // Comenzamos con 0 espacios de indentación
    return os;
}

void Elemento::imprimir(ostream &os, int indent) const
{
    os << string(indent * TAB_SIZE, ' ') << nombre()
       << " [" << volumen() << " m3] [" << peso() << " kg]"
       << endl;
}

Elemento::Elemento(const string &nombre, double volumen)
    : _nombre(nombre), _volumen(volumen) {}

std::string Elemento::nombre() const { return _nombre; }
double Elemento::volumen() const { return _volumen; }
