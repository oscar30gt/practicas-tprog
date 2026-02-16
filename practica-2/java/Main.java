import java.util.Stack;

public class Main {
    public static void main(String[] args) {
        Instruction[] instructionSet = {
            new Read(),
            new Read(),
            new Add(),
            new Dup(),
            new Write(),
            new JumpIf(0),
        };

        Program program = new Program(instructionSet);
        Stack<Integer> stack = new Stack<>();
        program.run(stack);
    }
}
