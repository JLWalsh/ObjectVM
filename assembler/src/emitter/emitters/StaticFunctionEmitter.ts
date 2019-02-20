import { StaticFunction } from "../../language/domain/Function";
import { Instruction } from "../../language/domain/Instruction";
import { IEmitter } from "../IEmitter";
import { IWriter } from "../IWriter";

export class StaticFunctionEmitter implements IEmitter<StaticFunction> {

  constructor(
    private readonly instructionEmitter: IEmitter<Instruction>,
  ) {}

  public emit(staticFunction: StaticFunction, writer: IWriter): void {
    staticFunction.getInstructions().forEach((instruction) => {
      this.instructionEmitter.emit(instruction, writer);
    });
  }

}
