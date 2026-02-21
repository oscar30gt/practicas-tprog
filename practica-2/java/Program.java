
/**
 * @file Program.java
 *
 * @authors
 * Hugo García Sánchez (930108)
 * Óscar Grimal Torres (926897)
 */

import java.util.Stack;

// ==========================================
// CLASE BASE
// ==========================================

/**
 * Clase que representa un programa ejecutable sobre una pila de enteros.
 *
 * @note Este "programa" no contiene instrucciones. En su lugar, considera
 *       instanciar
 *       algunos de los programas predefinidos (`AddProgram`,
 *       `CountdownProgram`, `FactorialProgram`)
 *       o crear otros heredando de esta clase.
 */
class Program {
    /** Conjunto de instrucciones ejecutables */
    protected final Instruction[] instructionSet;

    /**
     * Contructor protegido para crear programas a partir de un conjunto de
     * instrucciones.
     * 
     * @param instSet   Conjunto de instrucciones del programa.
     * @param instCount Cantidad de instrucciones en el conjunto.
     */
    protected Program(Instruction[] instSet) {
        this.instructionSet = instSet;
    }

    public Program() {
        this.instructionSet = null;
    }

    /**
     * Ejecuta el programa.
     */
    public void run() {
        Stack<Integer> stack = new Stack<>();
        for (int pc = 0; pc < instructionSet.length; pc++) {
            int targetLine = instructionSet[pc].execute(stack);
            if (targetLine >= 0) // Si la instrucción tiene como resultado un salto,
                                 // actualizamos el contador de programa.
                pc = targetLine - 1;
        }
    }

    @Override
    public String toString() {
        String text = "";
        for (int i = 0; i < instructionSet.length; i++) {
            text += String.format("%3d   %s\n", i , instructionSet[i].toString());
        }
        return text;
    }
}

// =========================================
// PROGRAMAS PREDEFINIDOS
// =========================================

/**
 * Programa que solicita dos números enteros y los suma,
 * imprimiendo el resultado obtenido.
 */
final class AddProgram extends Program {
    public AddProgram() {
        super(new Instruction[] {
                new Read(),
                new Read(),
                new Add(),
                new Write()
        });
    }
}

/**
 * Programa que solicita un número entero y muestra una cuenta atras desde
 * ese número hasta cero.
 */
final class CountdownProgram extends Program {
    public CountdownProgram() {
        super(new Instruction[] {
                new Read(),
                new Dup(),
                new Write(),
                new Push(-1),
                new Add(),
                new Dup(),
                new JumpIf(1)
        });
    }
}

/**
 * Programa que solicita un número entero y muestra su factorial.
 */
final class FactorialProgram extends Program {
    public FactorialProgram() {
        super(new Instruction[] {
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
                new Write()
        });
    }
}
