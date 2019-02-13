import { Argument } from "./Argument";
import { Opcode } from "./Opcode";

export class Instruction {

  public static for(opcode: Opcode): Instruction {
    return new Instruction(opcode, []);
  }

  private constructor(
    private readonly opcode: Opcode,
    private readonly args: Argument[],
  ) {}

  public withArg(arg: Argument) {
    this.args.push(arg);

    return this;
  }
}
