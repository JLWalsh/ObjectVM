import {Range} from '../../../math/Range';

export class IntegerOutOfRangeError {
  constructor(
      private readonly value: number,
      private readonly range: Range,
  ) {}
}