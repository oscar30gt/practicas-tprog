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
 * @note
 * Este "programa" no contiene instrucciones. En su lugar, considera instanciar
 * algunos de los programas predefinidos (`AddProgram`, `CountdownProgram`, `FactorialProgram`)
 * o crear otros heredando de esta clase.
 */
class Program
{
    /** Conjunto de instrucciones ejecutables */
    protected final Instruction[] instructionSet;

    /** n total de instrucciones */
    protected final int instructionCount;

    /**
     * Contructor protegido para crear programas a partir de un conjunto de instrucciones.
     * @param instSet Conjunto de instrucciones del programa.
     * @param instCount Cantidad de instrucciones en el conjunto.
     */
    protected Program(Instruction[] instSet, int instCount)
    {
        this.instructionSet = instSet;
        this.instructionCount = instCount;
    }

    public Program()
    {
        this.instructionSet = null;
        this.instructionCount = 0;
    }

    /**
     * Ejecuta el programa sobre la pila dada.
     * @param stack La pila de enteros sobre la que se ejecutará el programa.
     *              No es necesario que esté vacía: su contenido puede ser
     *              utilizado para pasar argumentos al programa.
     */
    public void run(Stack<Integer> stack)
    {
        for (int pc = 0; pc < instructionCount; pc++)
        {
            int targetLine = instructionSet[pc].execute(stack);
            if (targetLine >= 0) // Si la instrucción tiene como resultado un salto,
                                 // actualizamos el contador de programa.
                pc = targetLine - 1;
        }
    }

    @Override
    public String toString()
    {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < instructionCount; i++)
        {
            sb.append(String.format("%3d   %s\n", i + 1, instructionSet[i].toString()));
        }
        return sb.toString();
    }
}

// =========================================
// PROGRAMAS PREDEFINIDOS
// =========================================

/**
 * Programa que solicita dos números enteros y los suma,
 * imprimiendo el resultado obtenido.
 */
class AddProgram extends Program
{
    public AddProgram()
    {
        super(new Instruction[]{
                new Read(),
                new Read(),
                new Add(),
                new Write()
        }, 4);
    }
}

/**
 * Programa que solicita un número entero y muestra una cuenta atras desde
 * ese número hasta cero.
 */
class CountdownProgram extends Program
{
    public CountdownProgram()
    {
        super(new Instruction[]{
                new Read(),
                new Dup(),
                new Write(),
                new Push(-1),
                new Add(),
                new Dup(),
                new JumpIf(1)
        }, 7);
    }
}

/**
 * Programa que solicita un número entero y muestra su factorial.
 */
class FactorialProgram extends Program
{
    public FactorialProgram()
    {
        super(new Instruction[]{
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
        }, 14);
    }
}
