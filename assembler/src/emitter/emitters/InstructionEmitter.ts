import { Argument } from "../../language/domain/Argument";
import { Instruction } from "../../language/domain/Instruction";
import { Opcode } from "../../language/domain/Opcode";
import { IEmitter } from "../IEmitter";
import { IWriter } from "../IWriter";

export class InstructionEmitter implements IEmitter<Instruction> {

  constructor(
    private readonly opcodeEmitter: IEmitter<Opcode>,
    private readonly argumentEmitter: IEmitter<Argument[]>,
  ) {}

  public emit(instruction: Instruction, writer: IWriter): void {
    this.opcodeEmitter.emit(instruction.getOpcode(), writer);
    this.argumentEmitter.emit(instruction.getArguments(), writer);
  }

}
