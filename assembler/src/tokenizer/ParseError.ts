import { Coordinate } from "../Coordinate";

export class ParseError extends Error {

  private readonly coordinate: Coordinate;

  constructor(message: string, coordinate: Coordinate) {
    super(message);

    this.coordinate = coordinate;
  }
}
