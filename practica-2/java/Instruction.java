import java.util.Stack;
import java.util.Scanner;

public abstract class Instruction {
    protected final String instructionName;

    protected Instruction(String instName) {
        this.instructionName = instName;
    }

    @Override
    public String toString() {
        return instructionName;
    }

    public abstract int execute(Stack<Integer> stack);
}

abstract class InstructionWithImmediate extends Instruction {
    protected final int immediateValue;

    protected InstructionWithImmediate(String instName, int immVal) {
        super(instName + " " + immVal);
        this.immediateValue = immVal;
    }
}

final class Add extends Instruction {
    Add() {
        super("add");
    }

    @Override
    public int execute(Stack<Integer> stack) {
        if (stack.size() < 2) {
            throw new RuntimeException("Not enough values on the stack for 'add' instruction.");
        }

        int a = stack.pop();
        int b = stack.pop();
        stack.push(a + b);
        return -1;
    }
}

final class Read extends Instruction {
    private static final Scanner SCANNER = new Scanner(System.in);

    Read() {
        super("read");
    }

    @Override
    public int execute(Stack<Integer> stack) {
        System.out.print("? ");
        int value = SCANNER.nextInt();
        stack.push(value);
        return -1;
    }
}

final class Write extends Instruction {
    Write() {
        super("write");
    }

    @Override
    public int execute(Stack<Integer> stack) {
        if (stack.isEmpty()) {
            throw new RuntimeException("No values on the stack to write.");
        }

        int value = stack.pop();
        System.out.println(value);
        return -1;
    }
}

final class Push extends InstructionWithImmediate {
    Push(int val) {
        super("push", val);
    }

    @Override
    public int execute(Stack<Integer> stack) {
        stack.push(immediateValue);
        return -1;
    }
}

final class Dup extends Instruction {
    Dup() {
        super("dup");
    }

    @Override
    public int execute(Stack<Integer> stack) {
        if (stack.isEmpty()) {
            throw new RuntimeException("No values on the stack to duplicate.");
        }

        stack.push(stack.peek());
        return -1;
    }
}

final class JumpIf extends InstructionWithImmediate {
    JumpIf(int target) {
        super("jumpif", target);
    }

    @Override
    public int execute(Stack<Integer> stack) {
        if (stack.isEmpty()) {
            throw new RuntimeException("No values on the stack for 'jumpif' instruction.");
        }

        int value = stack.pop();
        return value >= 0 ? immediateValue : -1;
    }
}

final class Mul extends Instruction {
    Mul() {
        super("mul");
    }

    @Override
    public int execute(Stack<Integer> stack) {
        if (stack.size() < 2) {
            throw new RuntimeException("Not enough values on the stack for 'mul' instruction.");
        }

        int a = stack.pop();
        int b = stack.pop();
        stack.push(a * b);
        return -1;
    }
}

final class Swap extends Instruction {
    Swap() {
        super("swap");
    }

    @Override
    public int execute(Stack<Integer> stack) {
        if (stack.size() < 2) {
            throw new RuntimeException("Not enough values on the stack to swap.");
        }

        int a = stack.pop();
        int b = stack.pop();
        stack.push(a);
        stack.push(b);
        return -1;
    }
}

final class Over extends Instruction {
    Over() {
        super("over");
    }

    @Override
    public int execute(Stack<Integer> stack) {
        if (stack.size() < 2) {
            throw new RuntimeException("Not enough values on the stack for 'over' instruction.");
        }

        int a = stack.pop();
        int b = stack.peek();
        stack.push(a);
        stack.push(b);
        return -1;
    }
}
