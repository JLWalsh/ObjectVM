import { Lexeme } from "./Lexeme";
import { Token } from "./Token";

export class TokenizedLine {

  public static of(rawLine: string, lexemes: Lexeme[], lineNumber: number): TokenizedLine {
    return new TokenizedLine(rawLine, lexemes, lineNumber);
  }

  public static withError(rawLine: string, lexemesParsedSoFar: Lexeme[], lineNumber: number, error: Error) {
    return new TokenizedLine(rawLine, lexemesParsedSoFar, lineNumber, error);
  }

  private constructor(
    private readonly rawLine: string,
    private readonly lexemes: Lexeme[],
    private readonly lineNumber: number,
    private readonly error?: Error,
  ) {}
}
