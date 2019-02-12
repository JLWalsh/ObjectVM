import { ParsedToken } from "./ParsedToken";
import { ParseError } from "./ParseError";
import { Chars } from "./Token";

export class TokenizedLine {

  public constructor(
    private readonly rawLine: string,
    private readonly tokens: ParsedToken[],
    private readonly lineNumber: number,
    private readonly errors: ParseError[] = [],
  ) {}

  public toString() {
    return this.tokens.map((t) => t.toString())
                      .join(",");
  }
}
