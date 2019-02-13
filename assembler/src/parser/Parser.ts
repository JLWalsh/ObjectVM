import { TokenizedLine, TokenizedLineType } from "../tokenizer/TokenizedLine";
import { TokenizedProgram } from "../tokenizer/TokenizedProgram";

export class Parser {

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

  }

  private parseMetaInstruction(line: TokenizedLine) {

  }
}
