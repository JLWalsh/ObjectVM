
export class Range {
  public static fromTo(from: number, to: number): Range {
    return new Range(from, to);
  }

  private constructor(
      // TODO make sure the to < from
      private readonly from: number,
      private readonly to: number,
  ) {}

  public contains(value: number): boolean {
    return (value >= this.from) && (value <= this.to);
  }
}