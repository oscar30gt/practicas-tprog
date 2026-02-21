/**
 * @file Program.h
 *
 * @authors
 * Hugo García Sánchez (930108)
 * Óscar Grimal Torres (926897)
 */

#pragma once

#include <iostream>
#include "Instruction.h"

// ==========================================
// CLASE BASE
// ==========================================

/**
 * Clase que representa un programa ejecutable sobre una pila de enteros.
 *
 * @note
 * Este "programa" no contiene instrucciones. En su lugar, considera instanciar
 * algunos de los programas predefinidos (`AddProgram`, `CountdownProgram`, `FactorialProgram`)
 * o crear otros heredando de esta clase.
 */
class Program
{
protected:
    /** Conjunto de instrucciones ejecutables */
    const Instruction **instructionSet;

    /** n total de instrucciones */
    const unsigned instructionCount;

    /**
     * Contructor protegido para crear programas a partir de un conjunto de instrucciones.
     * @param instSet Conjunto de instrucciones del programa.
     * @param instCount Cantidad de instrucciones en el conjunto.
     */
    Program(const Instruction **instSet, int instCount);
    
public:
    Program();
    virtual ~Program();

    /**
     * Ejecuta el programa.
     */
    void run();

    friend std::ostream &operator<<(std::ostream &os, const Program &program);
};

/**
 * Sobrecarga del operador de inserción para la clase `Program`: imprime
 * el conjunto de instrucciones del programa de forma legible.
 */
std::ostream &operator<<(std::ostream &os, const Program &program);

// =========================================
// PROGRAMAS PREDEFINIDOS
// =========================================

/**
 * Programa que solicita dos números enteros y los suma,
 * imprimiendo el resultado obtenido.
 */
class AddProgram final : public Program
{
public:
    AddProgram();
};

/**
 * Programa que solicita un número entero y muestra una cuenta atras desde
 * ese número hasta cero.
 */
class CountdownProgram final : public Program
{
public:
    CountdownProgram();
};

/**
 * Programa que solicita un número entero y muestra su factorial.
 */
class FactorialProgram final : public Program
{
public:
    FactorialProgram();
};