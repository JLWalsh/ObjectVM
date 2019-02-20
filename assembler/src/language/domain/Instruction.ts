import {Size} from "../math/Size";
import {Argument} from "./Argument";
import {InstructionPrototype} from "./InstructionPrototype";
import { Opcode } from "./Opcode";

export class Instruction {
  constructor(
      private readonly prototype: InstructionPrototype,
      private readonly args: Argument[],
  ) {}

  public getSize(): Size {
    return this.args.reduce((totalSize, arg) => totalSize.addWith(arg.getSize()), Size.ZERO);
  }

  public getOpcode(): Opcode {
    return this.prototype.;
  }

  public getArguments(): Argument[] {
    return this.args;
  }
}
