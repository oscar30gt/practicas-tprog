#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <concepts>
#include "elemento.h"
#include "cargas.h"

using namespace std;

/**
 * Interfaz para elementos que pueden contener otras cargas
 */
template <typename T = Carga>
    requires derived_from<T, Carga>
class Almacen : public virtual Elemento
{
protected:
    /** Cargas almacenadas dentro de este almacen */
    vector<T *> _contenido;

    void imprimir(ostream &os, int indent) const override final;

public:
    /**
     * @param capacidad Capacidad máxima del almacen (en m3)
     */
    Almacen(const string &nombre, double capacidad);
    virtual ~Almacen() override;

    /**
     * Guarda una carga dentro del almacen, siempre que no exceda su capacidad.
     * @tparam T Tipo de carga a guardar, debe ser una clase derivada de Carga
     * @param carga Carga a guardar
     * @returns `true` si se ha guardado correctamente, `false` si no hay suficiente espacio.
     *
     * @note El almacen se hace cargo de la memoria de la carga guardada.
     * Si el almacen no tiene suficiente espacio, la carga no se guarda y el llamante
     * sigue siendo responsable de su memoria.
     */
    bool guardar(T *carga);
    virtual double peso() const override;
};

//==================================================================

/**
 * Un contenedor puede contener otras cargas al mismo tiempo que actua como una.
 */
template <typename T = Carga>
    requires derived_from<T, Carga>
class Contenedor final : public Carga, public Almacen<T>
{
public:
    /**
     * @param capacidad Capacidad máxima del contenedor (en m3)
     */
    Contenedor(double capacidad);
    ~Contenedor() override = default;

    // Resolvemos la ambiguedad de herencia multiple
    virtual double peso() const override { return Almacen<T>::peso(); }
};

/**
 * Un camion es un Almacen que puede guardar Cargas, pero no es una Carga que se pueda transportar dentro de otro Almacen.
 */
class Camion final : public Almacen<> // <- Un camion puede llevar lo que sea
{
public:
    /**
     * @param capacidad Capacidad máxima del camion (en m3)
     */
    Camion(double capacidad);
    ~Camion() override = default;
};

//==================================================================

template <typename T>
    requires derived_from<T, Carga>
Almacen<T>::Almacen(const string &nombre, double capacidad)
    : Elemento(nombre, capacidad) {}

template <typename T>
    requires derived_from<T, Carga>
Almacen<T>::~Almacen()
{
    for (Carga *carga : _contenido)
        delete carga;
}

template <typename T>
    requires derived_from<T, Carga>
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
    requires derived_from<T, Carga>
double Almacen<T>::peso() const
{
    double total = 0;
    for (const T *carga : _contenido)
        total += carga->peso();
    return total;
}

template <typename T>
    requires derived_from<T, Carga>
void Almacen<T>::imprimir(ostream &os, int indent) const
{
    // Encabezado generico. Igual que el de un producto.
    Elemento::imprimir(os, indent);

    // Imprimimos cada carga dentro del almacen, con indentación adicional
    for (const T *carga : _contenido)
        carga->imprimir(os, indent + 1); // Indentamos las cargas dentro del almacen
}

template <typename T>
    requires derived_from<T, Carga>
Contenedor<T>::Contenedor(double capacidad)
    : Elemento("Contenedor", capacidad),
      Carga("Contenedor", capacidad, 0),
      Almacen<T>("Contenedor", capacidad) {}

Camion::Camion(double capacidad)
    : Elemento("Camion", capacidad),
      Almacen<>("Camion", capacidad) {}