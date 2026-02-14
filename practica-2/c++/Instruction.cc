#include "Instruction.h"
#include <iostream>

std::string Instruction::toString() const
{
    return instructionName;
}

//=========================================

int Add::execute(std::stack<int> &stack) const
{
    if (stack.size() < 2)
    {
        throw std::runtime_error("Not enough values on the stack for 'add' instruction.");
    }

    int a = stack.top();
    stack.pop();
    int b = stack.top();
    stack.pop();
    stack.push(a + b);
    return -1;
}

int Read::execute(std::stack<int> &stack) const
{
    int value;
    std::cout << "? ";
    std::cin >> value;
    stack.push(value);
    return -1;
}

int Write::execute(std::stack<int> &stack) const
{
    if (stack.empty())
    {
        throw std::runtime_error("No values on the stack to write.");
    }

    int value = stack.top();
    stack.pop();
    std::cout << value << std::endl;
    return -1;
}

int Push::execute(std::stack<int> &stack) const
{
    stack.push(immediateValue);
    return -1;
}

int Dup::execute(std::stack<int> &stack) const
{
    if (stack.empty())
    {
        throw std::runtime_error("No values on the stack to duplicate.");
    }

    stack.push(stack.top());
    return -1;
}

int JumpIf::execute(std::stack<int> &stack) const
{
    if (stack.empty())
    {
        throw std::runtime_error("No values on the stack for 'jumpif' instruction.");
    }

    int value = stack.top();
    stack.pop();
    return value >= 0 ? immediateValue : -1;
}

int Mul::execute(std::stack<int> &stack) const
{
    if (stack.size() < 2)
    {
        throw std::runtime_error("Not enough values on the stack for 'mul' instruction.");
    }

    int a = stack.top();
    stack.pop();
    int b = stack.top();
    stack.pop();
    stack.push(a * b);
    return -1;
}

int Swap::execute(std::stack<int> &stack) const
{
    if (stack.size() < 2)
    {
        throw std::runtime_error("Not enough values on the stack to swap.");
    }

    int a = stack.top();
    stack.pop();
    int b = stack.top();
    stack.pop();
    stack.push(a);
    stack.push(b);
    return -1;
}

int Over::execute(std::stack<int> &stack) const
{
    if (stack.size() < 2)
    {
        throw std::runtime_error("Not enough values on the stack for 'over' instruction.");
    }

    int a = stack.top();
    stack.pop();
    int b = stack.top();
    stack.push(a);
    stack.push(b);
    return -1;
}