#include "practica3.h"
#include <iostream>

#define TAB_SIZE 2

//======================== Elemento ========================

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

//======================== Almacen ========================

Almacen::Almacen(double capacidad) : _capacidad(capacidad) {}
Almacen::~Almacen()
{
    for (Carga *carga : _contenido)
        delete carga;
}

bool Almacen::guardar(Carga *elemento)
{
    if (volumen() + elemento->volumen() > _capacidad)
        return false; // No hay suficiente espacio

    _contenido.push_back(elemento);
    return true;
}

double Almacen::volumen() const
{
    double total = 0;
    for (const Carga *carga : _contenido)
        total += carga->volumen();
    return total;
}

double Almacen::peso() const
{
    double total = 0;
    for (const Carga *carga : _contenido)
        total += carga->peso();
    return total;
}

void Almacen::imprimir(ostream &os, int indent) const
{
    // Encabezado generico. Igual que el de un producto.
    Elemento::imprimir(os, indent);

    // Imprimimos cada carga dentro del almacen, con indentación adicional
    for (const Carga *carga : _contenido)
        carga->imprimir(os, indent + 1); // Indentamos las cargas dentro del almacen
}

//======================== Producto ========================

Producto::Producto(const string &nombre, double volumen, double peso)
    : _nombre(nombre), _volumen(volumen), _peso(peso) {}

//======================== Contenedor ========================

Contenedor::Contenedor(double capacidad) : Almacen(capacidad) {}

//======================== Camion ========================

Camion::Camion(double capacidad) : Almacen(capacidad) {}