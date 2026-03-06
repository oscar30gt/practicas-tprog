/**
 * @file cargas.h
 *
 * @authors
 * Hugo García Sánchez (930108)
 * Óscar Grimal Torres (926897)
 */

#pragma once

#include "elemento.h"

/**
 * Interfaz para elementos que pueden ser transportados
 */
class Transportable : public virtual Elemento
{
    /** Peso propio de la carga (en kg) */
    const double _peso;

public:
    /**
     * @param nombre Nombre de la carga
     * @param volumen Volumen de la carga (en m3)
     * @param peso Peso de la carga (en kg)
     */
    Transportable(const std::string &nombre, double volumen, double peso);
    virtual ~Transportable() override = 0;

    virtual double peso() const override;
};

//==================================================================

class Carga : public Transportable
{
public:
    Carga(const std::string &nombre, double volumen, double peso);
};

/**
 * Una carga generica que se puede transportar.
 */
class Producto final : public Carga
{
public:
    /**
     * @param nombre Nombre del producto
     * @param volumen Volumen del producto (en m3)
     * @param peso Peso del producto (en kg)
     */
    Producto(const std::string &nombre, double volumen, double peso);
    ~Producto() override = default;
};

/**
 * Carga especial `SerVivo`.
 */
class SerVivo final : public Transportable
{
public:
    /**
     * @param nombre Nombre del ser vivo
     * @param volumen Volumen del ser vivo (en m3)
     * @param peso Peso del ser vivo (en kg)
     */
    SerVivo(const std::string &nombre, double volumen, double peso);
    ~SerVivo() override = default;
};

/**
 * Carga especial `Toxico`.
 */
class Toxico final : public Transportable
{
public:
    /**
     * @param nombre Nombre del tóxico
     * @param volumen Volumen del tóxico (en m3)
     * @param peso Peso del tóxico (en kg)
     */
    Toxico(const std::string &nombre, double volumen, double peso);
    ~Toxico() override = default;
};