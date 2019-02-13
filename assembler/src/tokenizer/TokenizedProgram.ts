import { TokenizedLine } from "./TokenizedLine";

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

  public hasErrors(): boolean {
    return !this.lines.every((line) => !line.hasErrors());
  }
}
