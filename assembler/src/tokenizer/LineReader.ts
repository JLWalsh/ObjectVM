
export type Char = string;

export class LineReader {

  public static from(line: string): LineReader {
    return new LineReader(line, 0, 0);
  }

  private constructor(
    private readonly line: string,
    private charPosition: number,
    private lastExtractCharPosition: number,
  ) {}

  public getPosition(): number {
    return this.charPosition;
  }

  public match(char: Char): boolean {
    if (this.peek() !== char) {
      return false;
    }

    this.advance();
    return true;
  }

  public matchFunc(matcher: (char: Char) => boolean) {
    const next = this.peek();

    return matcher(next);
  }

  public matchSequence(...chars: Char[]): boolean {
    const allMatch = chars.every((char, offset) => this.peek(offset) === char);
    if (allMatch) {
      this.charPosition += chars.length;
    }

    return allMatch;
  }

  public peek(offset: number = 0): Char {
    return this.line[this.charPosition + offset];
  }

  public advance(): Char {
    const char = this.peek();
    this.charPosition++;

    return char;
  }

  public isAtEnd(): boolean {
    return this.charPosition >= this.line.length;
  }

  public extract() {
    const extracted = this.line.substr(this.lastExtractCharPosition, this.charPosition);
    this.lastExtractCharPosition = this.charPosition;

    return extracted;
  }
}
