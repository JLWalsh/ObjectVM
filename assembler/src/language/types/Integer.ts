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
      const bitsForNumber = this.bitSize - Integer.SIGN_BIT_SIZE;
      const bitsForEachSign = bitsForNumber / 2;
      const maxValue = (2 ^ bitsForEachSign);
      const minValue = -((2 ^ bitsForEachSign) - 1);

      return Range.fromTo(minValue, maxValue);
    }
  }

  public static withSize(bitSize: number) {
    return new Integer.Builder(bitSize);
  }

  private constructor(
      private readonly bitSize: number, private readonly value: number) {}
}
