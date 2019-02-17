import {Argument} from "./Argument";
import {InstructionPrototype} from "./InstructionPrototype";
import { Opcode } from "./Opcode";

export class Instruction {
  constructor(
      private readonly prototype: InstructionPrototype,
      private readonly args: Argument[],
  ) {}

  public getSize(): number {
    return this.args.reduce((totalSize, arg) => totalSize + arg.getSize(), 0);
  }

  public getOpcode(): Opcode {
    return this.prototype.
  }

  public getArguments(): Argument[] {
    return this.args;
  }
}
