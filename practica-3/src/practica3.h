#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <concepts>

using namespace std;

//==================================================================
//========================= CLASES ABSTRACTAS ======================
//==================================================================

/**
 * Clase base abstracta para todo lo que tiene nombre, volumen y peso.
 */
class Elemento
{
    const string _nombre; // Nombre del elemento

protected:
    const double _volumen; // Volumen del elemento (en m3)

    // Auxiliar para imprimir con los niveles de indentación dados
    virtual void imprimir(ostream &os, int indent = 0) const;

public:
    Elemento(const string &nombre, double volumen);
    virtual ~Elemento() = default;

    // Sobrecarga del operador de inserción
    friend ostream &operator<<(ostream &os, const Elemento &e);

    // GETTERS
    /** Obtiene el nombre del elemento */
    string nombre() const;

    /** Obtiene el volumen del elemento */
    double volumen() const;

    /** Obtiene el peso del elemento */
    virtual double peso() const = 0;
};

/**
 * Interfaz para elementos que pueden ser transportados
 */
class Carga : public virtual Elemento
{
    const double _peso;   // Peso de la carga
    friend class Almacen<>; // Almacen necesita acceso a imprimir() para mostrar su contenido

public:
    Carga(const string &nombre, double volumen, double peso);
    virtual ~Carga() = default;

    virtual double peso() const override;
};

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
//========================= CLASES CONCRETAS =======================
//==================================================================

/**
 * Una carga simple que no contiene otras cargas. Tiene un peso y un volumen fijos.
 */
class Producto final : public Carga
{
public:
    /**
     * @param nombre Nombre del producto
     * @param volumen Volumen del producto (en m3)
     * @param peso Peso del producto (en kg)
     */
    Producto(const string &nombre, double volumen, double peso);
    ~Producto() override = default;
};

class SerVivo final : public Carga
{
public:
    /**
     * @param nombre Nombre del ser vivo
     * @param volumen Volumen del ser vivo (en m3)
     * @param peso Peso del ser vivo (en kg)
     */
    SerVivo(const string &nombre, double volumen, double peso);
    ~SerVivo() override = default;
};

class Toxico final : public Carga
{
public:
    /**
     * @param nombre Nombre del tóxico
     * @param volumen Volumen del tóxico (en m3)
     * @param peso Peso del tóxico (en kg)
     */
    Toxico(const string &nombre, double volumen, double peso);
    ~Toxico() override = default;
};

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