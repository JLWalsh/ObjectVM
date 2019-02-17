import {Range} from '../../../math/Range';

export class IntegerOutOfRangeError extends Error {
  constructor(
      private readonly value: number,
      private readonly range: Range,
  ) {
    super();
  }
}