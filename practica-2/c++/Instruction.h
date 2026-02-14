#pragma once

#include <string>
#include <stack>

class Instruction
{
protected:
    const std::string instructionName;

public:
    Instruction(std::string instName) : instructionName(instName) {};
    ~Instruction() = default;

    std::string toString() const;
    virtual int execute(std::stack<int> &stack) const = 0;
};

class InstructionWithImmediate : public Instruction
{
protected:
    const int immediateValue;

public:
    InstructionWithImmediate(std::string instName, int immVal)
        : Instruction(instName + " " + std::to_string(immVal)), immediateValue(immVal) {}
};

class Add final : public Instruction
{
public:
    Add() : Instruction("add") {}
    int execute(std::stack<int> &stack) const override;
};

class Read final : public Instruction
{
public:
    Read() : Instruction("read") {}
    int execute(std::stack<int> &stack) const override;
};

class Write final : public Instruction
{
public:
    Write() : Instruction("write") {}
    int execute(std::stack<int> &stack) const override;
};

class Push final : public InstructionWithImmediate
{
public:
    Push(int val)
        : InstructionWithImmediate("push", val) {}
    int execute(std::stack<int> &stack) const override;
};

class Dup final : public Instruction
{
public:
    Dup() : Instruction("dup") {}
    int execute(std::stack<int> &stack) const override;
};

class JumpIf final : public InstructionWithImmediate
{
public:
    JumpIf(int target)
        : InstructionWithImmediate("jumpif", target) {}
    int execute(std::stack<int> &stack) const override;
};

class Mul final : public Instruction
{
public:
    Mul() : Instruction("mul") {}
    int execute(std::stack<int> &stack) const override;
};

class Swap final : public Instruction
{
public:
    Swap() : Instruction("swap") {}
    int execute(std::stack<int> &stack) const override;
};

class Over final : public Instruction
{
public:
    Over() : Instruction("over") {}
    int execute(std::stack<int> &stack) const override;
};