/**
 * @file almacenes.h
 *
 * @authors
 * Hugo García Sánchez (930108)
 * Óscar Grimal Torres (926897)
 */

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <concepts>

#include "elemento.h"
#include "transportables.h"

/**
 * Interfaz para elementos que pueden contener otras cargas
 * @tparam T Tipo de carga que puede contener el almacen, debe ser una clase derivada de `Transportable`
 */
template <typename T>
requires std::derived_from<T, Transportable>
class Almacen : public virtual Elemento
{    
    /** Cargas almacenadas dentro de este almacen */
    std::vector<T *> _contenido;

    /** Uso actual del almacen (en m3) */
    double _volumenOcupado;
    
    // Sobreescibimos imprimir para mostrar tambien el contenido del almacen
    void imprimir(std::ostream &os, int indent) const override final;

public:
    /**
     * @param nombre Nombre del almacen
     * @param capacidad Capacidad máxima del almacen (en m3)
     */
    Almacen(const std::string &nombre, double capacidad);
    virtual ~Almacen() override = 0;

    /**
     * Guarda una carga dentro del almacen, siempre que no exceda su capacidad.
     * @tparam T Tipo de carga a guardar, debe ser una clase derivada de `Transportable`
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

/**
 * Un contenedor puede contener transportables de un tipo específico al 
 * mismo tiempo que actua como una carga estandar que puede ser transportada.
 */
template <typename T>
requires std::derived_from<T, Transportable>
class Contenedor final : public Carga, public Almacen<T>
{
public:
    /**
     * @param capacidad Capacidad máxima del contenedor (en m3)
     */
    Contenedor(double capacidad);
    ~Contenedor() override = default;

    // Resolvemos la ambiguedad de herencia multiple
    // El peso de un contenedor es el peso de las cargas que contiene, el contenedor 
    // en sí no tiene peso propio [bueno si, pero no lo tenemos en cuenta :)]
    virtual double peso() const override { return Almacen<T>::peso(); }
};

/**
 * Un camion es un Almacen que puede guardar cargas estandar,
 * pero no es una carga en si mismo.
 */
class Camion final : public Almacen<Carga> // <- Un camion es un almacen de cargas estandar.
{
public:
    /**
     * @param capacidad Capacidad máxima del camion (en m3)
     */
    Camion(double capacidad);
    ~Camion() override = default;
};

//========================= IMPLEMENTACION =========================

// Helper para obtener el nombre de un contenedor segun el tipo de carga que almacena
template <typename T>
requires std::derived_from<T, Transportable>
constexpr const char *nombreContenedor()
{
    if constexpr (std::same_as<T, SerVivo>)
        return "Contenedor de seres vivos";
    else if constexpr (std::same_as<T, Toxico>)
        return "Contenedor de productos toxicos";
    else if constexpr (std::same_as<T, Producto>)
        return "Contenedor de productos basicos";
    else
        return "Contenedor de carga estandar";
}

template <typename T>
requires std::derived_from<T, Transportable>
Almacen<T>::Almacen(const std::string &nombre, double capacidad)
    : Elemento(nombre, capacidad) {}

template <typename T>
requires std::derived_from<T, Transportable>
Almacen<T>::~Almacen()
{
    for (Transportable *carga : _contenido)
        delete carga;
}

template <typename T>
requires std::derived_from<T, Transportable>
bool Almacen<T>::guardar(T *carga)
{
    if (_volumenOcupado + carga->volumen() > volumen())
        return false; // No hay suficiente espacio

    _contenido.push_back(carga);
    _volumenOcupado += carga->volumen();
    return true;
}

template <typename T>
requires std::derived_from<T, Transportable>
double Almacen<T>::peso() const
{
    // El peso de un almacen es la suma del peso de las cargas que contiene
    double total = 0;
    for (const T *carga : _contenido)
        total += carga->peso();
    return total;
}

template <typename T>
requires std::derived_from<T, Transportable>
void Almacen<T>::imprimir(std::ostream &os, int indent) const
{
    // Encabezado generico. Igual que el de una carga cualquiera.
    Elemento::imprimir(os, indent);

    // Imprimimos cada carga dentro del almacen, con indentación adicional
    for (const T *carga : _contenido)
        carga->imprimir(os, indent + 1); // Indentamos las cargas dentro del almacen
}

template <typename T>
requires std::derived_from<T, Transportable>
Contenedor<T>::Contenedor(double capacidad)
    : Elemento(nombreContenedor<T>(), capacidad),
      Carga(nombreContenedor<T>(), capacidad, 0),
      Almacen<T>(nombreContenedor<T>(), capacidad) {}

Camion::Camion(double capacidad)
    : Elemento("Camion", capacidad),
      Almacen<Carga>("Camion", capacidad) {}