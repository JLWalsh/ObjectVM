import {ParseError} from '../parser/ParseError';

import {SyntaxError} from '../tokenizer/SyntaxError';
import {Instruction} from './Instruction';
import {MetaInstruction} from './MetaInstruction';

export enum LineType {
  META,
  INSTRUCTION,
}

export class Line {
  public static fromInstruction(instruction: Instruction): Line {
    return new Line(LineType.INSTRUCTION, instruction);
  }

  public static fromMetaInstruction(metaInstruction: MetaInstruction): Line {
    return new Line(LineType.META, metaInstruction);
  }

  public static fromError(type: LineType, error: ParseError): Line {
    return new Line(type, undefined, [error]);
  }

  private constructor(
      private readonly type: LineType,
      private readonly value: Instruction|MetaInstruction|void,
      private readonly errors: ParseError[] = []) {}

  public withErrors(errors: ParseError[]) {
    return new Line(this.type, this.value, errors);
  }

  public asInstruction(): Instruction {
    if (!(this.value instanceof Instruction)) {
      throw new Error(`Attempted to get line as Instruction but was actually ${
          typeof (this.value)}`)
    }

    return this.value;
  }

  public asMetaInstruction(): MetaInstruction {
    if (!(this.value instanceof MetaInstruction)) {
      throw new Error(
          `Attempted to get line as MetaInstruction but was actually ${
              typeof (this.value)}`)
    }

    return this.value;
  }
}