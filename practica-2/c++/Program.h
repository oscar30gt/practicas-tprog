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
#include <stack>

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
    ~Program();

    /**
     * Ejecuta el programa sobre la pila dada.
     * @param stack La pila de enteros sobre la que se ejecutará el programa.
     *              No es necesario que esté vacía: su contenido puede ser
     *              utilizado para pasar argumentos al programa.
     */
    void run(std::stack<int> &stack);

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
class AddProgram : public Program
{
public:
    AddProgram();
};

/**
 * Programa que solicita un número entero y muestra una cuenta atras desde
 * ese número hasta cero.
 */
class CountdownProgram : public Program
{
public:
    CountdownProgram();
};

/**
 * Programa que solicita un número entero y muestra su factorial.
 */
class FactorialProgram : public Program
{
public:
    FactorialProgram();
};