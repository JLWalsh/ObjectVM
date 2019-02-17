import {Range} from '../../math/Range';
import {IntegerOutOfRangeError} from './errors/IntegerOutOfRangeError';

export class Integer {
  private static SIGN_BIT_SIZE = 1;

  private static Builder = class Builder {
    constructor(private readonly bitSize: number) {}

    public createWithValue(value: number) {
      const range = this.getValueRange();
      if (!range.contains(value)) {
        throw new IntegerOutOfRangeError(value, range);
      }

      return new Integer(this.bitSize, value);
    }

    private getValueRange(): Range {
      const maxValue = (Math.pow(2, this.bitSize)) / 2;
      const minValue = -(maxValue - 1);

      return Range.fromTo(minValue, maxValue);
    }
  }

  public static withSize(bitSize: number) {
    return new Integer.Builder(bitSize);
  }

  private constructor(
      private readonly bitSize: number, private readonly value: number) {}

  public getValue(): number {
    return this.value;
  }
}
