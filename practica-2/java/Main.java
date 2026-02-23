/**
 * @file Main.java
 *
 * @authors
 * Hugo García Sánchez (930108)
 * Óscar Grimal Torres (926897)
 */

/**
 * Programa principal: ejecuta los 3 programas predefinidos
 * (`AddProgram`, `CountdownProgram`, `FactorialProgram`) sobre
 * una pila de enteros.
 */
public class Main {
    public static void main(String[] args) {
        Program addProgram = new AddProgram();
        Program countdownProgram = new CountdownProgram();
        Program factorialProgram = new FactorialProgram();

        // AddProgram
        System.out.println("\033[33mEjecutando AddProgram:\033[0m");
        System.out.println(addProgram);
        addProgram.run();

        // CountdownProgram
        System.out.println("\n\n\033[33mEjecutando CountdownProgram:\033[0m");
        System.out.println(countdownProgram);
        countdownProgram.run();

        // FactorialProgram
        System.out.println("\n\n\033[33mEjecutando FactorialProgram:\033[0m");
        System.out.println(factorialProgram);
        factorialProgram.run();
    }
}
