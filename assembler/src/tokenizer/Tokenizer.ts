import { Coordinate } from "../Coordinate";
import { Program } from "../Program";
import { Char } from "./Char";
import { Lexeme, LexemeType } from "./Lexeme";
import { LineReader } from "./LineReader";
import { Token } from "./Token";
import { TokenizedLine } from "./TokenizedLine";

type Char = string;

export class Tokenizer {

  private lexemes: Lexeme[] = [];
  private lineReader?: LineReader;
  private currentLine: number = 0;

  public tokenize(program: Program): TokenizedLine[] {
    const lines = program.getAllLines();

    return lines.map(this.tokenizeLine);
  }

  private tokenizeLine(line: string): TokenizedLine {
    this.lineReader = LineReader.from(line);

    while (this.lineReader.isAtEnd()) {
      const currentChar = this.lineReader.advance();

      if (this.matchTokens(Token.SLASH, Token.SLASH)) {
        break;
      } else if (this.matchTokens(Token.HASH)) {
        this.addLexeme(LexemeType.META_START);
      } else if (this.matchTokens(Token.COLON, Token.COLON)) {
        this.addLexeme(LexemeType.BODY_DECLARATION);
      } else if (this.matchTokens(Token.LEFT_PAREN)) {
        this.addLexeme(LexemeType.LEFT_PAREN);
      } else if (this.matchTokens(Token.RIGHT_PAREN)) {
        this.addLexeme(LexemeType.RIGHT_PAREN);
      } else if (this.matchTokens(Token.DASH, Token.GREATER_THAN)) {
        this.addLexeme(LexemeType.IMPLEMENTATION);
      } else if (Char.isAlpha(currentChar)) {

      } else if (Char.isNumeric(currentChar)) {

      } else {

      }
    }

    return new TokenizedLine("", [], 0);
  }

  private matchTokens(...tokensToMatch: Token[]): boolean {
    if (!this.lineReader) {
      return false;
    }

    return tokensToMatch.every((t) => this.lineReader!.match(t));
  }

  private addLexeme(lexemeType: LexemeType) {
    if (!this.lineReader) {
      throw new Error("Illegal state: line reader is undefined");
    }

    const coordinate = this.getCurrentCoordinates();
    const rawValue = this.lineReader.extract();
    const parsedToken = new Lexeme(rawValue, lexemeType, coordinate);

    this.lexemes.push(parsedToken);
  }

  private getCurrentCoordinates(): Coordinate {
    if (!this.lineReader) {
      return Coordinate.at({
        line: this.currentLine,
      });
    }

    return Coordinate.at({
      column: this.lineReader.getPosition(),
      line: this.currentLine,
    });
  }
}
