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

Elemento::Elemento(const string &nombre, double volumen)
    : _nombre(nombre), _volumen(volumen) {}

std::string Elemento::nombre() const { return _nombre; }
double Elemento::volumen() const { return _volumen; }

//======================== Carga ========================

Carga::Carga(const string &nombre, double volumen, double peso)
    : Elemento(nombre, volumen), _peso(peso) {}

double Carga::peso() const { return _peso; }

//======================== Almacen ========================

Almacen::Almacen(const string &nombre, double capacidad)
    : Elemento(nombre, capacidad){}

Almacen::~Almacen()
{
    for (Carga *carga : _contenido)
        delete carga;
}

bool Almacen::guardar(Carga *carga)
{
    double uso = 0;
    for (const Carga *c : _contenido)
        uso += c->volumen();

    if (uso + carga->volumen() > volumen())
        return false; // No hay suficiente espacio

    _contenido.push_back(carga);
    return true;
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
    : Carga(nombre, volumen, peso) {}

//======================== Contenedor ========================

Contenedor::Contenedor(double capacidad)
    : Carga("Contenedor", capacidad, 0), Almacen("Contenedor", capacidad) {}

//======================== Camion ========================

Camion::Camion(double capacidad)
    : Almacen("Camion", capacidad) {}