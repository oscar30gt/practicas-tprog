/**
 * @file main.cc
 *
 * @authors
 * Hugo García Sánchez (930108)
 * Óscar Grimal Torres (926897)
 */

#include "Program.h"
#include "Instruction.h"
#include <stack>
#include <iostream>

using namespace std;

/**
 * Programa principal: ejecuta los 3 programas predefinidos
 * (`AddProgram`, `CountdownProgram`, `FactorialProgram`) sobre
 * una pila de enteros.
 */
int main()
{
    stack<int> stack;
    AddProgram addProgram;
    CountdownProgram countdownProgram;
    FactorialProgram factorialProgram;

    // AddProgram
    cout << "\033[33mEjecutando AddProgram:\033[0m\n"
         << addProgram << endl;
    addProgram.run(stack);

    // CountdownProgram
    cout << "\n\n\033[33mEjecutando CountdownProgram:\033[0m\n"
         << countdownProgram << endl;
    countdownProgram.run(stack);

    // FactorialProgram
    cout << "\n\n\033[33mEjecutando FactorialProgram:\033[0m\n"
         << factorialProgram << endl;
    factorialProgram.run(stack);

    return 0;
}