import {Coordinate} from '../Coordinate';

export class SyntaxError {
  private readonly coordinate: Coordinate;
  private readonly message: string;

  constructor(message: string, coordinate: Coordinate) {
    this.message = message;
    this.coordinate = coordinate;
  }

  public toString() {
    return `[${this.coordinate.toString()}]: ${this.message}`;
  }
}
