import {Argument} from './Argument';
import {InstructionPrototype} from './InstructionPrototype';

export class Instruction {
  constructor(
      private readonly prototype: InstructionPrototype,
      private readonly args: Argument[],
  ) {}
}