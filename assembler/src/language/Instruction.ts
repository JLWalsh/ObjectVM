import { Token } from "../tokenizer/ParsedToken";
import { Argument, ArgumentType } from "./Argument";
import { Opcode } from "./Opcode";

export class Instruction {

  public static for(opcode: Opcode): Instruction {
    return new Instruction(opcode, []);
  }

  private constructor(
    private readonly opcode: Opcode,
    private readonly args: ArgumentType[],
  ) {}

  public isFor(opcode: Opcode): boolean {
    return this.opcode === opcode;
  }

  public getArgs(): ArgumentType[] {
    return this.args;
  }

  public withArg(arg: ArgumentType) {
    this.args.push(arg);

    return this;
  }
}
