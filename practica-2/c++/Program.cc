/**
 * @file Program.cc
 *
 * @authors
 * Hugo García Sánchez (930108)
 * Óscar Grimal Torres (926897)
 */

#include "Program.h"
#include "Instruction.h"
#include <iomanip>
#include <stack>

// ==========================================
// CLASE BASE
// ==========================================

Program::Program()
    : instructionSet(nullptr), instructionCount(0) {};

Program::Program(const Instruction **instSet, int instCount)
    : instructionSet(instSet), instructionCount(instCount) {}

Program::~Program()
{
    // El destructor de `Program` es responsable de liberar la memoria de las instrucciones
    // y es comun para todos los programas predefinidos, no es virtual.
    for (unsigned i = 0; i < instructionCount; i++)
        delete instructionSet[i];
    delete[] instructionSet;
}

void Program::run()
{
    std::stack<int> stack;
    for (unsigned pc = 0; pc < instructionCount; pc++)
    {
        int targetLine = instructionSet[pc]->execute(stack);
        if (targetLine >= 0) // Si la instrucción tiene como resultado un salto,
                             // actualizamos el contador de programa.
            pc = targetLine - 1;
    }
}

std::ostream &operator<<(std::ostream &os, const Program &program)
{
    for (unsigned i = 0; i < program.instructionCount; i++)
        os << std::setw(3) << i + 1 << "   "
           << program.instructionSet[i]->toString()
           << std::endl;
    return os;
}

// ==========================================
// PROGRAMAS PREDEFINIDOS
// ==========================================

AddProgram::AddProgram()
    : Program(new const Instruction *[4]{
                  new Read(),
                  new Read(),
                  new Add(),
                  new Write()},
              4) {};

CountdownProgram::CountdownProgram()
    : Program(new const Instruction *[7]{
                  new Read(),
                  new Dup(),
                  new Write(),
                  new Push(-1),
                  new Add(),
                  new Dup(),
                  new JumpIf(1)},
              7) {};

FactorialProgram::FactorialProgram()
    : Program(new const Instruction *[14]{
                  new Push(1),
                  new Read(),
                  new Swap(),
                  new Over(),
                  new Mul(),
                  new Swap(),
                  new Push(-1),
                  new Add(),
                  new Dup(),
                  new Push(-2),
                  new Add(),
                  new JumpIf(2),
                  new Swap(),
                  new Write()},
              14) {};
