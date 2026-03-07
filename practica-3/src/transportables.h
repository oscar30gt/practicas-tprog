/**
 * @file transportables.h
 *
 * @authors
 * Hugo García Sánchez (930108)
 * Óscar Grimal Torres (926897)
 */

#pragma once

#include "elemento.h"
#include <concepts>

/**
 * Interfaz para elementos que pueden ser transportados
 */
class Transportable : public virtual Elemento
{
    /** Peso propio del transportable (en kg) */
    const double _peso;

    // Necesitamos que `Almacen` pueda acceder a `imprimir()` para poder imprimir su contenido
    template <typename T>
    requires std::derived_from<T, Transportable>
    friend class Almacen;

public:
    /**
     * @param nombre Nombre del transportable
     * @param volumen Volumen del transportable (en m3)
     * @param peso Peso del transportable (en kg)
     */
    Transportable(const std::string &nombre, double volumen, double peso);
    virtual ~Transportable() override = 0;

    virtual double peso() const override;
};

//==================================================================

// Clase carga, que mas que como carga generica podemos entenderla como "carga no especial"
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