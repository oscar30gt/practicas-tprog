#pragma once

#include <iostream>
#include <string>

using namespace std;

/**
 * Clase base abstracta para todo lo que tiene nombre, volumen y peso.
 */
class Elemento
{
    const string _nombre; // Nombre del elemento

protected:
    const double _volumen; // Volumen del elemento (en m3)

public:
    // Auxiliar para imprimir con los niveles de indentación dados
    virtual void imprimir(ostream &os, int indent = 0) const;

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
