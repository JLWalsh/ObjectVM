import { ParsedToken, TokenType } from "./ParsedToken";
import { ParseError } from "./ParseError";
import { Chars } from "./Token";

export enum TokenizedLineType {
  INSTRUCTION,
  META_INSTRUCTION,
  NOTHING,
}

export class TokenizedLine {

  public constructor(
    private readonly rawLine: string,
    private readonly tokens: ParsedToken[],
    private readonly lineNumber: number,
    private readonly errors: ParseError[] = [],
  ) {}

  public hasErrors(): boolean {
    return this.errors.length > 0;
  }

  public isOfType(type: TokenizedLineType): boolean {
    return this.getType() === type;
  }

  public getTokens(): ParsedToken[] {
    return this.tokens;
  }

  public toString() {
    return this.tokens.map((t) => t.toString())
                      .join(",");
  }

  private getType(): TokenizedLineType {
    if (this.tokens.length === 0) {
      return TokenizedLineType.NOTHING;
    }

    if (this.tokens[0].is(TokenType.META_START)) {
      return TokenizedLineType.META_INSTRUCTION;
    }

    return TokenizedLineType.INSTRUCTION;
  }
}
