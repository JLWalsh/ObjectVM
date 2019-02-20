
export class IncrementalNumberGenerator {
  private lastGeneratedValue: number = 0;

  public generateNext(): number {
    return this.lastGeneratedValue++;
  }
}