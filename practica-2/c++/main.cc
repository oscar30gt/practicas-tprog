#include "Program.h"
#include "Instruction.h"

int main()
{
    Instruction* instructionSet[] = {
        new Read(),
        new Read(),
        new Add(),
        new Dup(),
        new Write(),

        new JumpIf(0),
    };

    Program program(instructionSet, 7);
    std::stack<int> stack;
    program.run(stack);
    return 0;
}