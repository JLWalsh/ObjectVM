
export class Program {
  public static fromString(source: string): Program {
    return new Program(source);
  }

  private constructor(
      private readonly source: string,
  ) {}

  public getAllLines(): string[] {
    return this.source.split('\n');
  }
}
