/**
 * @file Instruction.h
 *
 * @authors
 * Hugo García Sánchez (930108)
 * Óscar Grimal Torres (926897)
 */

#pragma once

#include <string>
#include <stack>

// ==========================================
// CLASES BASE
// ==========================================

/**
 * Clase abstracta que representa una instrucción ejecutable sobre
 * una pila de enteros de una máquina virtual.
 */
class Instruction
{
protected:
    /** Nombre amigable de la instrucción */
    const std::string instructionName;
    Instruction(std::string instName);

public:
    virtual ~Instruction() = default;

    /**
     * Devuelve una representación en forma de cadena de la instrucción.
     */
    std::string toString() const;

    /**
     * Ejecuta la instrucción sobre la pila dada.
     * @param stack La pila de enteros sobre la que se ejecutará la instrucción.
     * @returns Nueva posición del contador de programa después de ejecutar la instrucción.
     * `-1` para seguir con la ejecución normal del programa
     */
    virtual int execute(std::stack<int> &stack) const = 0;
};

/**
 * Clase abstracta que representa una instrucción con valor inmediato.
 */
class InstructionWithImmediate : public Instruction
{
protected:
    /** Valor inmediato de la instrucción */
    const int immediateValue;

public:
    InstructionWithImmediate(std::string instName, int immVal);
};

// ==========================================
// DEFINICION DE INSTRUCCIONES
// ==========================================

// Add: Suma los dos elementos superiores de la pila,
//      los elimina y deja el resultado en la cima de la pila.
class Add final : public Instruction
{
public:
    Add() : Instruction("add") {}
    int execute(std::stack<int> &stack) const override;
};

// Read: Lee un entero desde la entrada estándar y lo 
//       coloca en la cima de la pila.
class Read final : public Instruction
{
public:
    Read() : Instruction("read") {}
    int execute(std::stack<int> &stack) const override;
};

// Write: Elimina el elemento superior de la pila y lo escribe
//        en la salida estándar.
class Write final : public Instruction
{
public:
    Write() : Instruction("write") {}
    int execute(std::stack<int> &stack) const override;
};

// Push: Coloca el valor inmediato en la cima de la pila.
class Push final : public InstructionWithImmediate
{
public:
    Push(int val) : InstructionWithImmediate("push", val) {}
    int execute(std::stack<int> &stack) const override;
};

// Dup: Duplica la cima de la pila
class Dup final : public Instruction
{
public:
    Dup() : Instruction("dup") {}
    int execute(std::stack<int> &stack) const override;
};

// JumpIf: Elimina el elemento superior de la pila y, si es distinto de cero,
//         salta a la posición dada por el valor inmediato.
class JumpIf final : public InstructionWithImmediate
{
public:
    JumpIf(int target)
        : InstructionWithImmediate("jumpif", target) {}
    int execute(std::stack<int> &stack) const override;
};

// Mul: Multiplica los dos elementos superiores de la pila,
//      los elimina y deja el resultado en la cima de la pila.
class Mul final : public Instruction
{
public:
    Mul() : Instruction("mul") {}
    int execute(std::stack<int> &stack) const override;
};

// Swap: Intercambia los dos elementos superiores de la pila.
class Swap final : public Instruction
{
public:
    Swap() : Instruction("swap") {}
    int execute(std::stack<int> &stack) const override;
};

// Over: Duplica el segundo elemento superior de la pila, colocandolo
//       en la cima de la misma.
class Over final : public Instruction
{
public:
    Over() : Instruction("over") {}
    int execute(std::stack<int> &stack) const override;
};