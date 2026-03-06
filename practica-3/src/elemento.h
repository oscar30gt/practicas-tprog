/**
 * @file elemento.h
 *
 * @authors
 * Hugo García Sánchez (930108)
 * Óscar Grimal Torres (926897)
 */

#pragma once

#include <iostream>
#include <string>

/**
 * Clase base abstracta para todo lo que tiene nombre, volumen y peso.
 */
class Elemento
{
    /** Nombre amigable del elemento */
    const std::string _nombre;

protected:
    /** Volumen que ocupa el elemento (en m3) */
    const double _volumen;

public:
    // Auxiliar para imprimir con los niveles de indentación dados
    virtual void imprimir(std::ostream &os, int indent = 0) const;

    /**
     * @param nombre Nombre del elemento.
     * @param volumen Volumen que ocupa el elemento (en m3).
     */
    Elemento(const std::string &nombre, double volumen);
    virtual ~Elemento() = default;

    // Sobrecarga del operador de inserción
    friend std::ostream &operator<<(std::ostream &os, const Elemento &e);

    // GETTERS
    /** Obtiene el nombre del elemento */
    std::string nombre() const;

    /** Obtiene el volumen del elemento */
    double volumen() const;

    /** Obtiene el peso del elemento */
    virtual double peso() const = 0;
};
