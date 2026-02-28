#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;

//==================================================================
//========================= CLASES ABSTRACTAS ======================
//==================================================================

/**
 * Clase base abstracta para todo lo que tiene nombre, volumen y peso.
 */
class Elemento
{
protected:
    // Auxiliar para imprimir con los niveles de indentación dados
    virtual void imprimir(ostream &os, int indent = 0) const;

public:
    virtual ~Elemento() = default;

    // GETTERS
    /** Obtiene el nombre del elemento */
    virtual string nombre() const = 0;

    /** Obtiene el volumen del elemento */
    virtual double volumen() const = 0;

    /** Obtiene el peso del elemento */
    virtual double peso() const = 0;

    // Sobrecarga del operador de inserción
    friend ostream &operator<<(ostream &os, const Elemento &e);
};

/**
 * Interfaz para elementos que pueden ser transportados
 */
class Carga : public virtual Elemento
{
    friend class Almacen; // Almacen necesita acceso a imprimir() para mostrar su contenido
public:
    virtual ~Carga() = default;
};

/**
 * Interfaz para elementos que pueden contener otras cargas
 */
class Almacen : public virtual Elemento
{
protected:
    vector<Carga *> _contenido;
    double _capacidad;

    void imprimir(ostream &os, int indent) const override final;

public:
    /**
     * @param capacidad Capacidad máxima del almacen (en m3)
     */
    Almacen(double capacidad);
    virtual ~Almacen() override;

    /**
     * Guarda una carga dentro del almacen, siempre que no exceda su capacidad.
     * @param elemento Carga a guardar
     * @returns `true` si se ha guardado correctamente, `false` si no hay suficiente espacio.
     *
     * @note El almacen se hace cargo de la memoria de la carga guardada.
     * Si el almacen no tiene suficiente espacio, la carga no se guarda y el llamante
     * sigue siendo responsable de su memoria.
     */
    bool guardar(Carga *elemento);
    virtual string nombre() const = 0;
    double volumen() const override;
    double peso() const override;
};

//==================================================================
//========================= CLASES CONCRETAS =======================
//==================================================================

/**
 * Una carga simple que no contiene otras cargas. Tiene un peso y un volumen fijos.
 */
class Producto : public Carga
{
    const string _nombre;  // Nombre del producto
    const double _volumen; // Volumen del producto
    const double _peso;    // Peso del producto

public:
    /**
     * @param nombre Nombre del producto
     * @param volumen Volumen del producto (en m3)
     * @param peso Peso del producto (en kg)
     */
    Producto(const string &nombre, double volumen, double peso);
    ~Producto() override = default;

    string nombre() const override { return _nombre; }
    double volumen() const override { return _volumen; }
    double peso() const override { return _peso; }
};

/**
 * Un contenedor puede contener otras cargas al mismo tiempo que actua como una.
 */
class Contenedor : public Carga, public Almacen
{
public:
    /**
     * @param capacidad Capacidad máxima del contenedor (en m3)
     */
    Contenedor(double capacidad);
    ~Contenedor() override = default;

    string nombre() const override { return "Contenedor"; }
};

/**
 * Un camion es un Almacen que puede guardar Cargas, pero no es una Carga que se pueda transportar dentro de otro Almacen.
 */
class Camion : public Almacen
{
public:
    /**
     * @param capacidad Capacidad máxima del camion (en m3)
     */
    Camion(double capacidad);
    ~Camion() override = default;

    string nombre() const override { return "Camion"; }
};