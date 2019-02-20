import {Size} from "../math/Size";
import {Instruction} from "./Instruction";

export class StaticFunction {
  constructor(
      protected readonly numberOfArguments: number,
      protected readonly instructions: Instruction[],
      protected readonly name: string) {}

  public isNamed(name: string): boolean {
    return this.name === name;
  }

  public getSize(): Size {
    return this.instructions.reduce(
        (totalSize, instruction) => totalSize.addWith(instruction.getSize()), Size.ZERO);
  }

  public getNumberOfArguments(): number {
    return this.numberOfArguments;
  }

  public getInstructions(): Instruction[] {
    return this.instructions;
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
