/**
 * @file Main.java
 *
 * @authors
 * Hugo García Sánchez (930108)
 * Óscar Grimal Torres (926897)
 */

import java.util.Stack;

/**
 * Programa principal: ejecuta los 3 programas predefinidos
 * (`AddProgram`, `CountdownProgram`, `FactorialProgram`) sobre
 * una pila de enteros.
 */
public class Main
{
    public static void main(String[] args)
    {
        Stack<Integer> stack = new Stack<>();
        AddProgram addProgram = new AddProgram();
        CountdownProgram countdownProgram = new CountdownProgram();
        FactorialProgram factorialProgram = new FactorialProgram();

        // AddProgram
        System.out.println("\033[33mEjecutando AddProgram:\033[0m");
        System.out.println(addProgram);
        addProgram.run(stack);

        // CountdownProgram
        System.out.println("\n\n\033[33mEjecutando CountdownProgram:\033[0m");
        System.out.println(countdownProgram);
        countdownProgram.run(stack);

        // FactorialProgram
        System.out.println("\n\n\033[33mEjecutando FactorialProgram:\033[0m");
        System.out.println(factorialProgram);
        factorialProgram.run(stack);
    }
}
