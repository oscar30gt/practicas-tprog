#pragma once
#include <iostream>
#include "Instruction.h"
#include <stack>

class Program
{
    Instruction **instructionSet;
    const unsigned instructionCount;

public:
    Program(Instruction **instructions, unsigned instructionCount)
        : instructionSet(instructions),
          instructionCount(instructionCount) {}
    ~Program();

    void run(std::stack<int> &stack);
    friend std::ostream &operator<<(std::ostream &os, const Program &program);
};

std::ostream &operator<<(std::ostream &os, const Program &program);