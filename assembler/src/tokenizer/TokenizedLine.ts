import {Chars} from './Chars';
import {Token, TokenType} from './ParsedToken';
import {SyntaxError} from './SyntaxError';

export enum TokenizedLineType {
  INSTRUCTION,
  META_INSTRUCTION,
  NOTHING,
}

export class TokenizedLine {
  public constructor(
      private readonly rawLine: string,
      private readonly tokens: Token[],
      private readonly lineNumber: number,
      private readonly errors: SyntaxError[] = [],
  ) {}

  public hasErrors(): boolean {
    return this.errors.length > 0;
  }

  public isOfType(type: TokenizedLineType): boolean {
    return this.getType() === type;
  }

  public isEmpty(): boolean {
    return this.getType() === TokenizedLineType.NOTHING;
  }

  public getTokens(): Token[] {
    return this.tokens;
  }

  public getErrors(): SyntaxError[] {
    return this.errors;
  }

  public toString() {
    return this.tokens.map((t) => t.toString()).join(',');
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
