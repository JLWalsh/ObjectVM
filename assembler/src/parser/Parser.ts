import {Argument, ArgumentType} from '../language/Argument';
import {Instruction} from '../language/Instruction';
import {InstructionPrototype} from '../language/InstructionPrototype';
import {Line, LineType} from '../language/Line';
import {MetaInstructionType} from '../language/MetaInstruction';
import {Opcode} from '../language/Opcode';
import {TokenType} from '../tokenizer/ParsedToken';
import {SyntaxError} from '../tokenizer/SyntaxError';
import {TokenizedLine, TokenizedLineType} from '../tokenizer/TokenizedLine';
import {TokenizedProgram} from '../tokenizer/TokenizedProgram';

import {ArgumentParser} from './ArgumentParser';
import {IKeywordParser} from './IKeywordParser';
import {ParsedProgram} from './ParsedProgram';
import {ParseError} from './ParseError';
import {FromEnumMetaInstructionTypeParser} from './parsers/FromEnumMetaInstructionTypeParser';
import {FromEnumOpcodeParser} from './parsers/FromEnumOpcodeParser';
import {TokenReader} from './TokenReader';

export class Parser {
  public static withDefaultInstructions(): Parser {
    const instructions = [
      InstructionPrototype.for(Opcode.NEW).withArg(ArgumentType.CLASS_REF),
      InstructionPrototype.for(Opcode.UI_PUSH).withArg(ArgumentType.UINT),
      InstructionPrototype.for(Opcode.UI_PRINT),
      InstructionPrototype.for(Opcode.RETURN_VOID),
      InstructionPrototype.for(Opcode.LOCAL_LOAD).withArg(ArgumentType.UINT),
      InstructionPrototype.for(Opcode.UI_GLOBAL_STORE)
          .withArg(ArgumentType.UINT),
      InstructionPrototype.for(Opcode.UI_GLOBAL_LOAD)
          .withArg(ArgumentType.UINT),
      InstructionPrototype.for(Opcode.RETURN),
      InstructionPrototype.for(Opcode.INVOKE_VIRTUAL)
          .withArg(ArgumentType.FUNC_REF),
      InstructionPrototype.for(Opcode.DUP),
      InstructionPrototype.for(Opcode.INVOKE_STATIC)
          .withArg(ArgumentType.STATIC_FUNC_REF),
      InstructionPrototype.for(Opcode.HALT),
    ];

    return new Parser(
        new FromEnumOpcodeParser(),
        new FromEnumMetaInstructionTypeParser(),
        new Map(),
        instructions,
    );
  }

  constructor(
      private readonly opcodeParser: IKeywordParser<Opcode>,
      private readonly metaInstructionTypeParser:
          IKeywordParser<MetaInstructionType>,
      private readonly argumentParsers: Map<ArgumentType, ArgumentParser>,
      private readonly instructions: InstructionPrototype[],
  ) {}

  public parse(tokenizedProgram: TokenizedProgram) {
    if (tokenizedProgram.hasErrors()) {
      throw new Error('Attempted to parse program with lexical errors');
    }

    const lines: Line[] = [];
    tokenizedProgram.getLines().forEach((tokenizedLine) => {
      const line = this.parseLine(tokenizedLine);
      if (line) {
        lines.push(line);
      }
    });

    return new ParsedProgram(lines);
  }

  private parseLine(line: TokenizedLine) {
    if (line.isOfType(TokenizedLineType.META_INSTRUCTION)) {
      this.parseMetaInstruction(line);
    } else if (line.isOfType(TokenizedLineType.INSTRUCTION)) {
      return this.parseInstruction(line);
    }
  }

  private parseInstruction(line: TokenizedLine): Line|void {
    if (line.isEmpty()) {
      return;
    }

    const reader = TokenReader.from(line);
    const rawOpcode = reader.advance();
    const opcode =
        this.opcodeParser.parse(rawOpcode.getParsedValue() as string);
    if (!opcode) {
      const error = new ParseError(`Unrecognized opcode: ${opcode}`);
      return Line.fromError(LineType.INSTRUCTION, error);
    }

    const instructionPrototype = this.instructions.find((i) => i.isFor(opcode));
    if (!instructionPrototype) {
      throw new Error(
          `Illegal state: no instruction defined for opcode ${opcode}.`);
    }

    const parsedArguments: Argument[] = [];
    const parseErrors: ParseError[] = [];
    instructionPrototype.getArgs().forEach(arg => {
      const argumentParser = this.findParserFor(arg);
      if (!argumentParser) {
        throw new Error(`Illegal state: no parser defined for argument ${arg}`);
      }

      const parsed = argumentParser.parse(reader);
      if (parsed instanceof ParseError) {
        parseErrors.push(parsed);
      }

      parsedArguments.push(parsed as Argument);
    });

    const instruction = new Instruction(instructionPrototype, parsedArguments);

    return Line.fromInstruction(instruction).withErrors(parseErrors);
  }

  private parseMetaInstruction(line: TokenizedLine) {}

  private findParserFor(argType: ArgumentType): ArgumentParser|void {
    return this.argumentParsers.get(argType);
  }
}
