#include "Program.h"
#include "Instruction.h"

Program::~Program()
{
    for (unsigned i = 0; i < instructionCount; i++)
        delete instructionSet[i];
    delete[] instructionSet;
}

void Program::run(std::stack<int> &stack)
{
    for (unsigned pc = 0; pc < instructionCount; pc++)
    {
        int targetLine = instructionSet
        [pc]->execute(stack);
        if (targetLine >= 0)
            pc = targetLine - 1;
    }
}

std::ostream &operator<<(std::ostream &os, const Program &program)
{
    for (unsigned i = 0; i < program.instructionCount; i++)
        os << program.instructionSet[i]->toString() << std::endl;
    return os;
}
