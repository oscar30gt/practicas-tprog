#pragma once

#include "elemento.h"

/**
 * Interfaz para elementos que pueden ser transportados
 */
class Carga : public virtual Elemento
{
    const double _peso;     // Peso de la carga

public:
    Carga(const string &nombre, double volumen, double peso);
    virtual ~Carga() = default;

    virtual double peso() const override;
};

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