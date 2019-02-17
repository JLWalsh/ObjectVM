
export class Coordinate {
  public static at({line, column}: {line: number, column?: number}):
      Coordinate {
    return new Coordinate(line, column);
  }

  public static zero(): Coordinate {
    return Coordinate.at({line: 0, column: 0});
  }

  private constructor(
      private readonly line: number,
      private readonly column?: number,
  ) {}

  public toString() {
    return `${this.line}` + this.column ? this.column : '';
  }
}
