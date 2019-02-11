
export class Coordinate {

  public static at({ line, column }: { line: number, column?: number }): Coordinate {
    return new Coordinate(line, column);
  }

  private constructor(
    private readonly line: number,
    private readonly column?: number,
  ) {}
}
