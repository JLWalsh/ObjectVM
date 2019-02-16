import {SyntaxError} from '../tokenizer/SyntaxError';

export class ParsedLine {
  constructor(
      private readonly errors: SyntaxError[],
  ) {}
}
