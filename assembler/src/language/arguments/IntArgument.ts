import {Argument, ArgumentType} from '../Argument';

export class IntArgument extends Argument {
  constructor(private readonly value: number) {
    super(ArgumentType.INT);
  }

  public getValue(): number {
    return this.value;
  }
}