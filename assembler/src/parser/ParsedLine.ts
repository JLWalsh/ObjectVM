import { ParseError } from "../tokenizer/ParseError";

export class ParsedLine {

  constructor(
    private readonly errors: ParseError[],
  ) {}
}
