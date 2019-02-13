import { Coordinate } from "../Coordinate";
import { Program } from "../Program";
import { Char } from "./Char";
import { LineReader } from "./LineReader";
import { ParsedToken, TokenType } from "./ParsedToken";
import { ParseError } from "./ParseError";
import { Chars } from "./Token";
import { TokenizedLine } from "./TokenizedLine";
import { TokenizedProgram } from "./TokenizedProgram";

export class Tokenizer {

  private lexemes: ParsedToken[] = [];
  private errors: ParseError[] = [];
  private lineReader?: LineReader;
  private currentLine: number = 0;

  public tokenize(program: Program): TokenizedProgram {
    const lines = program.getAllLines();

    const tokenizedLines = lines.map((line) => this.tokenizeLine(line));

    return new TokenizedProgram(tokenizedLines);
  }

  private tokenizeLine(line: string): TokenizedLine {
    this.lineReader = LineReader.from(line);
    this.lexemes = [];
    this.errors = [];

    while (!this.lineReader.isAtEnd()) {
      if (this.lineReader.matchSequence(Chars.SLASH, Chars.SLASH)) {
        break;
      }

      if (this.lineReader.matchSequence(Chars.WHITESPACE)) {
        continue;
      }

      if (this.lineReader.matchSequence(Chars.HASH)) {
        this.addLexeme(TokenType.META_START);
      } else if (this.lineReader.matchSequence(Chars.COLON, Chars.COLON)) {
        this.addLexeme(TokenType.BODY_DECLARATION);
      } else if (this.lineReader.matchSequence(Chars.LEFT_PAREN)) {
        this.addLexeme(TokenType.LEFT_PAREN);
      } else if (this.lineReader.matchSequence(Chars.RIGHT_PAREN)) {
        this.addLexeme(TokenType.RIGHT_PAREN);
      } else if (this.lineReader.matchSequence(Chars.DASH)) {
        if (this.lineReader.matchSequence(Chars.GREATER_THAN)) {
          this.addLexeme(TokenType.IMPLEMENTATION);
        } else {
          this.parseNumber();
        }
      } else if (this.lineReader.matchSequence(Chars.QUOTE)) {
        this.parseString();
      } else if (this.lineReader.matchFunc(Char.isAlpha)) {
        this.parseWord();
      } else if (this.lineReader.matchFunc(Char.isNumeric)) {
        this.parseNumber();
      } else {
        const unrecognizedChar = this.lineReader.advance();
        this.addError(`Unrecognized character: ${unrecognizedChar}`);
      }
    }

    return new TokenizedLine(line, this.lexemes, this.currentLine, this.errors);
  }

  private parseWord() {
    while (!this.lineReader!.isAtEnd() && Char.isAlpha(this.lineReader!.peek())) {
      this.lineReader!.advance();
    }

    const word = this.lineReader!.extract();
    const lexeme = new ParsedToken(word, word, TokenType.WORD, this.getCurrentCoordinates());
    this.lexemes.push(lexeme);
  }

  private parseString() {
    let parsedString = "";

    while (!this.lineReader!.isAtEnd() && this.lineReader!.peek() !== Chars.QUOTE) {
      parsedString += this.lineReader!.advance();

      if (this.lineReader!.match(Chars.ESCAPE_NEXT_CHAR)) {
        parsedString += this.lineReader!.advance();
      }
    }

    if (!this.lineReader!.match(Chars.QUOTE)) {
      this.addError("Unterminated string.");
    }

    const stringLiteral = this.lineReader!.extract();
    const lexeme = new ParsedToken(stringLiteral, parsedString, TokenType.STRING, this.getCurrentCoordinates());
    this.lexemes.push(lexeme);
  }

  private parseNumber() {
    while (!this.lineReader!.isAtEnd() && this.lineReader!.matchFunc(Char.isPartOfNumber)) {
      // do nothing
    }

    const numberLiteral = this.lineReader!.extract();
    const parsedNumber = Number(numberLiteral);

    if (isNaN(parsedNumber)) {
      this.addError(`Failed to parse number: ${parsedNumber}.`);
    }

    const lexeme = new ParsedToken(numberLiteral, parsedNumber, TokenType.NUMBER, this.getCurrentCoordinates());
    this.lexemes.push(lexeme);
  }

  private addLexeme(lexemeType: TokenType) {
    if (!this.lineReader) {
      throw new Error("Illegal state: line reader is undefined");
    }

    const coordinate = this.getCurrentCoordinates();
    const rawValue = this.lineReader.extract();
    const parsedToken = new ParsedToken(rawValue, rawValue, lexemeType, coordinate);

    this.lexemes.push(parsedToken);
  }

  private addError(message: string) {
    const error = new ParseError(message, this.getCurrentCoordinates());
    this.errors.push(error);
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
