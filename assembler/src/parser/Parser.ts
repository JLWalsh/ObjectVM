import { ArgumentType } from "../language/Argument";
import { Instruction } from "../language/Instruction";
import { MetaInstructionType } from "../language/MetaInstruction";
import { Opcode } from "../language/Opcode";
import { ParseError } from "../tokenizer/ParseError";
import { TokenizedLine, TokenizedLineType } from "../tokenizer/TokenizedLine";
import { TokenizedProgram } from "../tokenizer/TokenizedProgram";
import { IKeywordParser } from "./IKeywordParser";
import { FromEnumMetaInstructionTypeParser } from "./parsers/FromEnumMetaInstructionTypeParser";
import { FromEnumOpcodeParser } from "./parsers/FromEnumOpcodeParser";
import { TokenReader } from "./TokenReader";
import { TokenType } from "../tokenizer/ParsedToken";

export class Parser {

  public static withDefaultInstructions(): Parser {
    const instructions = [
      Instruction.for(Opcode.NEW).withArg(ArgumentType.CLASS_REF),
      Instruction.for(Opcode.UI_PUSH).withArg(ArgumentType.UINT),
      Instruction.for(Opcode.UI_PRINT),
      Instruction.for(Opcode.RETURN_VOID),
      Instruction.for(Opcode.LOCAL_LOAD).withArg(ArgumentType.UINT),
      Instruction.for(Opcode.UI_GLOBAL_STORE).withArg(ArgumentType.UINT),
      Instruction.for(Opcode.UI_GLOBAL_LOAD).withArg(ArgumentType.UINT),
      Instruction.for(Opcode.RETURN),
      Instruction.for(Opcode.INVOKE_VIRTUAL).withArg(ArgumentType.FUNC_REF),
      Instruction.for(Opcode.DUP),
      Instruction.for(Opcode.INVOKE_STATIC).withArg(ArgumentType.STATIC_FUNC_REF),
      Instruction.for(Opcode.HALT),
    ];

    return new Parser(
      new FromEnumOpcodeParser(),
      new FromEnumMetaInstructionTypeParser(),
      instructions,
    );
  }

  private errors: ParseError[] = [];

  constructor(
    private readonly opcodeParser: IKeywordParser<Opcode>,
    private readonly metaInstructionTypeParser: IKeywordParser<MetaInstructionType>,
    private readonly instructions: Instruction[],
  ) {}

  public parse(tokenizedProgram: TokenizedProgram) {
    if (tokenizedProgram.hasErrors()) {
      throw new Error("Attempted to parse program with lexical errors");
    }

    tokenizedProgram.getLines().forEach((line) => {
      this.errors = [];

      this.parseLine(line);
    });
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

    const reader = TokenReader.from(line);
    const rawOpcode = reader.advance();
    const opcode = this.opcodeParser.parse(rawOpcode.getParsedValue() as string);
    if (!opcode) {
      this.addError(`Unrecognized opcode: ${opcode}`);
      return;
    }

    const instruction = this.instructions.find((i) => i.isFor(opcode));
    if(!instruction) {
      throw new Error(`Illegal state: no instruction defined for opcode ${opcode}.`);
    }

    const instructionArgs = instruction.getArgs().map(arg => this.argsParser.parse(arg, line));
  }

  private parseMetaInstruction(line: TokenizedLine) {

  }

  private addError(message: string) {

  }
}
