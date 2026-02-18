/**
 * @file Instruction.java
 *
 * @authors
 * Hugo García Sánchez (930108)
 * Óscar Grimal Torres (926897)
 */

import java.util.Stack;
import java.util.Scanner;

// ==========================================
// CLASES BASE
// ==========================================

/**
 * Clase abstracta que representa una instrucción ejecutable sobre
 * una pila de enteros de una máquina virtual.
 */
abstract class Instruction
{
    /** Nombre amigable de la instrucción */
    protected final String instructionName;

    public Instruction(String instName)
    {
        this.instructionName = instName;
    }

    /**
     * Devuelve una representación en forma de cadena de la instrucción.
     */
    public String toString()
    {
        return instructionName;
    }

    /**
     * Ejecuta la instrucción sobre la pila dada.
     * @param stack La pila de enteros sobre la que se ejecutará la instrucción.
     * @returns Nueva posición del contador de programa después de ejecutar la instrucción.
     * `-1` para seguir con la ejecución normal del programa
     */
    public abstract int execute(Stack<Integer> stack);
}

/**
 * Clase abstracta que representa una instrucción con valor inmediato.
 */
abstract class InstructionWithImmediate extends Instruction
{
    /** Valor inmediato de la instrucción */
    protected final int immediateValue;

    public InstructionWithImmediate(String instName, int immVal)
    {
        super(instName + " " + immVal);
        this.immediateValue = immVal;
    }
}

// ==========================================
// DEFINICION DE INSTRUCCIONES
// ==========================================

// Add: Suma los dos elementos superiores de la pila,
//      los elimina y deja el resultado en la cima de la pila.
final class Add extends Instruction
{
    public Add()
    {
        super("add");
    }

    @Override
    public int execute(Stack<Integer> stack)
    {
        if (stack.size() < 2)
        {
            throw new RuntimeException("Not enough values on the stack for 'add' instruction.");
        }

        int a = stack.pop();
        int b = stack.pop();
        stack.push(a + b);
        return -1;
    }
}

// Read: Lee un entero desde la entrada estándar y lo 
//       coloca en la cima de la pila.
final class Read extends Instruction
{
    private static Scanner scanner = new Scanner(System.in);

    public Read()
    {
        super("read");
    }

    @Override
    public int execute(Stack<Integer> stack)
    {
        System.out.print("? ");
        int value = scanner.nextInt();
        stack.push(value);
        return -1;
    }
}

// Write: Elimina el elemento superior de la pila y lo escribe
//        en la salida estándar.
final class Write extends Instruction
{
    public Write()
    {
        super("write");
    }

    @Override
    public int execute(Stack<Integer> stack)
    {
        if (stack.empty())
        {
            throw new RuntimeException("No values on the stack to write.");
        }

        int value = stack.pop();
        System.out.println(value);
        return -1;
    }
}

// Push: Coloca el valor inmediato en la cima de la pila.
final class Push extends InstructionWithImmediate
{
    public Push(int val)
    {
        super("push", val);
    }

    @Override
    public int execute(Stack<Integer> stack)
    {
        stack.push(immediateValue);
        return -1;
    }
}

// Dup: Duplica la cima de la pila
final class Dup extends Instruction
{
    public Dup()
    {
        super("dup");
    }

    @Override
    public int execute(Stack<Integer> stack)
    {
        if (stack.empty())
        {
            throw new RuntimeException("No values on the stack to duplicate.");
        }

        stack.push(stack.peek());
        return -1;
    }
}

// JumpIf: Elimina el elemento superior de la pila y, si es distinto de cero,
//         salta a la posición dada por el valor inmediato.
final class JumpIf extends InstructionWithImmediate
{
    public JumpIf(int target)
    {
        super("jumpif", target);
    }

    @Override
    public int execute(Stack<Integer> stack)
    {
        if (stack.empty())
        {
            throw new RuntimeException("No values on the stack for 'jumpif' instruction.");
        }

        int value = stack.pop();
        return value >= 0 ? immediateValue : -1;
    }
}

// Mul: Multiplica los dos elementos superiores de la pila,
//      los elimina y deja el resultado en la cima de la pila.
final class Mul extends Instruction
{
    public Mul()
    {
        super("mul");
    }

    @Override
    public int execute(Stack<Integer> stack)
    {
        if (stack.size() < 2)
        {
            throw new RuntimeException("Not enough values on the stack for 'mul' instruction.");
        }

        int a = stack.pop();
        int b = stack.pop();
        stack.push(a * b);
        return -1;
    }
}

// Swap: Intercambia los dos elementos superiores de la pila.
final class Swap extends Instruction
{
    public Swap()
    {
        super("swap");
    }

    @Override
    public int execute(Stack<Integer> stack)
    {
        if (stack.size() < 2)
        {
            throw new RuntimeException("Not enough values on the stack to swap.");
        }

        int a = stack.pop();
        int b = stack.pop();
        stack.push(a);
        stack.push(b);
        return -1;
    }
}

// Over: Duplica el segundo elemento superior de la pila, colocandolo
//       en la cima de la misma.
final class Over extends Instruction
{
    public Over()
    {
        super("over");
    }

    @Override
    public int execute(Stack<Integer> stack)
    {
        if (stack.size() < 2)
        {
            throw new RuntimeException("Not enough values on the stack for 'over' instruction.");
        }

        int a = stack.pop();
        int b = stack.peek();
        stack.push(a);
        stack.push(b);
        return -1;
    }
}
