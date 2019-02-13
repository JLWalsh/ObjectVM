import { Argument } from "../language/Argument";
import { Instruction } from "../language/Instruction";
import { Opcode } from "../language/Opcode";
import { TokenizedLine, TokenizedLineType } from "../tokenizer/TokenizedLine";
import { TokenizedProgram } from "../tokenizer/TokenizedProgram";
import { FromEnumOpcodeParser } from "./FromEnumOpcodeParser";
import { IKeywordParser } from "./IKeywordParser";

export class Parser {

  public static withDefaultInstructions(): Parser {
    const instructions = [
      Instruction.for(Opcode.NEW).withArg(Argument.CLASS_REF),
      Instruction.for(Opcode.UI_PUSH).withArg(Argument.UINT),
      Instruction.for(Opcode.UI_PRINT),
      Instruction.for(Opcode.RETURN_VOID),
      Instruction.for(Opcode.LOCAL_LOAD).withArg(Argument.UINT),
      Instruction.for(Opcode.UI_GLOBAL_STORE).withArg(Argument.UINT),
      Instruction.for(Opcode.UI_GLOBAL_LOAD).withArg(Argument.UINT),
      Instruction.for(Opcode.RETURN),
      Instruction.for(Opcode.INVOKE_VIRTUAL).withArg(Argument.FUNC_REF),
      Instruction.for(Opcode.DUP),
      Instruction.for(Opcode.INVOKE_STATIC).withArg(Argument.STATIC_FUNC_REF),
      Instruction.for(Opcode.HALT),
    ];

    return new Parser(new FromEnumOpcodeParser(), instructions);
  }

  constructor(
    private readonly opcodeParser: IKeywordParser<Opcode>,
    private readonly instructions: Instruction[],
  ) {}

  public parse(tokenizedProgram: TokenizedProgram) {
    if (tokenizedProgram.hasErrors()) {
      throw new Error("Attempted to parse program with lexical errors");
    }

    tokenizedProgram.getLines().forEach((line) => this.parseLine(line));
  }

  private parseLine(line: TokenizedLine) {
    if (line.isOfType(TokenizedLineType.META_INSTRUCTION)) {
      this.parseMetaInstruction(line);
    } else if (line.isOfType(TokenizedLineType.INSTRUCTION)) {
      this.parseInstruction(line);
    }
  }

  private parseInstruction(line: TokenizedLine) {
    if (line.isOfType(TokenizedLineType.NOTHING)) {
      return;
    }

    const tokens = line.getTokens();
    const rawOpcode = tokens[0].getParsedValue() as string;
    const opcode = this.opcodeParser.parse(rawOpcode);
  }

  private parseMetaInstruction(line: TokenizedLine) {

  }
}
