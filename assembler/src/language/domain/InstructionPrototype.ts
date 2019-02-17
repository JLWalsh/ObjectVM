import {ArgumentType} from './Argument';
import {Opcode} from './Opcode';

export class InstructionPrototype {
  public static for(opcode: Opcode): InstructionPrototype {
    return new InstructionPrototype(opcode, []);
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
