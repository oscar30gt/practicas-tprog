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

template <typename T>
Almacen<T>::Almacen(const string &nombre, double capacidad)
    : Elemento(nombre, capacidad) {}

template <typename T>
Almacen<T>::~Almacen()
{
    for (Carga *carga : _contenido)
        delete carga;
}

template <typename T>
bool Almacen<T>::guardar(T *carga)
{
    double uso = 0;
    for (const T *c : _contenido)
        uso += c->volumen();

    if (uso + carga->volumen() > volumen())
        return false; // No hay suficiente espacio

    _contenido.push_back(carga);
    return true;
}

template <typename T>
double Almacen<T>::peso() const
{
    double total = 0;
    for (const T *carga : _contenido)
        total += carga->peso();
    return total;
}

template <typename T>
void Almacen<T>::imprimir(ostream &os, int indent) const
{
    // Encabezado generico. Igual que el de un producto.
    Elemento::imprimir(os, indent);

    // Imprimimos cada carga dentro del almacen, con indentación adicional
    for (const T *carga : _contenido)
        carga->imprimir(os, indent + 1); // Indentamos las cargas dentro del almacen
}

//======================== Producto/Ser Vivo/Toxico ========================

Producto::Producto(const string &nombre, double volumen, double peso)
    : Elemento(nombre, volumen), Carga(nombre, volumen, peso) {}

SerVivo::SerVivo(const string &nombre, double volumen, double peso)
    : Elemento(nombre, volumen), Carga(nombre, volumen, peso) {}

Toxico::Toxico(const string &nombre, double volumen, double peso)
    : Elemento(nombre, volumen), Carga(nombre, volumen, peso) {}

//======================== Contenedor ========================

template <typename T>
Contenedor<T>::Contenedor(double capacidad)
    : Carga("Contenedor", capacidad, 0), Almacen<T>("Contenedor", capacidad) {}

//======================== Camion ========================

Camion::Camion(double capacidad)
    : Elemento("Camion", capacidad), Almacen<Carga>("Camion", capacidad) {}