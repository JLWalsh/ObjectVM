import {Instruction} from '../Instruction';

export class StaticFunction {
  constructor(
      protected readonly numberOfArguments: number,
      protected readonly instructions: Instruction[],
      protected readonly name: string) {}

  public isNamed(name: string): boolean {
    return this.name === name;
  }

  public getBytecodeSize(): number {
    return 0;
  }

  public getNumberOfArguments(): number {
    return this.numberOfArguments;
  }
}

export class ClassFunction extends StaticFunction {
  private readonly functionsImplemented: ClassFunction[];

  constructor(
      numberOfArguments: number, instructions: Instruction[],
      functionsImplemented: ClassFunction[], name: string) {
    super(numberOfArguments, instructions, name);

    this.functionsImplemented = functionsImplemented;
  }

  public isVirtual(): boolean {
    return this.instructions.length === 0;
  }
}
