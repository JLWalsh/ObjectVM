import { Token, TokenType } from "../tokenizer/ParsedToken";
import { TokenizedLine } from "../tokenizer/TokenizedLine";

export class TokenReader {

  public static from(line: TokenizedLine): TokenReader {
    return new TokenReader(line.getTokens());
  }

  private position: number = 0;
  private lastExtractPosition: number = 0;
  
  private constructor(
    private readonly tokens: Token[],
  ) {}

  public getPosition(): number {
    return this.position;
  }

  public match(value: TokenType): Token | void {
    if (this.peek().is(value)) {
      return undefined;
    }

    return this.advance();
  }

  public matchSequence(...values: TokenType[]): boolean {
    const allMatch = values.every((value, offset) => this.peek(offset).is(value));
    if (allMatch) {
      this.position += values.length;
    }

    return allMatch;
  }

  public peek(offset: number = 0): Token {
    return this.tokens[this.position + offset];
  }

  public advance(): Token {
    const char = this.peek();
    this.position++;

    return char;
  }

  public isAtEnd(): boolean {
    return this.position >= this.tokens.length;
  }

  // public extract(): Token {
  //   const extractedValue = this.extractFromTo(this.lastExtractPosition, this.position);
  //   this.lastExtractPosition = this.position;

  //   return extractedValue;
  // }
}