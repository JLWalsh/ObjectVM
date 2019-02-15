import { Argument, ArgumentType } from "../language/Argument";
import { Instruction } from "../language/Instruction";
import { Opcode } from "../language/Opcode";

export class ParsedInstruction {

  private constructor(
    private readonly opcode: Opcode,
    private readonly args: Argument[],
  ) {}
}
