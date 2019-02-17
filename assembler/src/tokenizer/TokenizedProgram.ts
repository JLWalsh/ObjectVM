import {TokenizedLine} from './TokenizedLine';

export class TokenizedProgram {
  constructor(
      private readonly lines: TokenizedLine[],
  ) {}

  public getLines(): TokenizedLine[] {
    return this.lines;
  }

  public getLine(index: number): TokenizedLine {
    return this.lines[index];
  }

  public getErrors(): SyntaxError[] {
    return this.lines.reduce(
        (errors: SyntaxError[], l) => errors.concat(l.getErrors()), []);
  }

  public hasErrors(): boolean {
    return !this.lines.some((line) => !line.hasErrors());
  }
}
