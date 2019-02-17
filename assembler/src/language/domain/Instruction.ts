import {Argument} from './Argument';
import {InstructionPrototype} from './InstructionPrototype';

export class Instruction {
  constructor(
      private readonly prototype: InstructionPrototype,
      private readonly args: Argument[],
  ) {}

  public getSize(): number {
    return this.args.reduce((totalSize, arg) => totalSize + arg.getSize(), 0);
  }
}