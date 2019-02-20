import {Range} from "../../../math/Range";

export class NumericOutOfRangeError {
  constructor(
      private readonly value: number,
      private readonly range: Range,
  ) {}
}
