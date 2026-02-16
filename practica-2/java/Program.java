import java.util.Stack;

public class Program {
    private final Instruction[] instructionSet;

    public Program(Instruction[] instructions) {
        this.instructionSet = instructions;
    }

    public void run(Stack<Integer> stack) {
        int pc = 0;
        while (pc < instructionSet.length) {
            int targetLine = instructionSet[pc].execute(stack);
            if (targetLine >= 0) {
                pc = targetLine;
            } else {
                pc++;
            }
        }
    }

    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        for (Instruction instruction : instructionSet) {
            builder.append(instruction.toString()).append(System.lineSeparator());
        }
        return builder.toString();
    }
}
