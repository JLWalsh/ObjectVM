import {Coordinate} from '../Coordinate';

export class SyntaxError extends Error {
  private readonly coordinate: Coordinate;

  constructor(message: string, coordinate: Coordinate) {
    super(message);

    this.coordinate = coordinate;
  }
}
