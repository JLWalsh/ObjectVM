import {Range} from "../../math/Range";

import {IntegerOutOfRangeError} from "./errors/IntegerOutOfRangeError";

export class UnsignedInteger {

  public static withSize(bitSize: number) {
    return new UnsignedInteger.Builder(bitSize);
  }
  private static Builder = class Builder {
    constructor(private readonly bitSize: number) {}

    public createWithValue(value: number) {
      const range = this.getValueRange();
      if (!range.contains(value)) {
        throw new IntegerOutOfRangeError(value, range);
      }

      return new UnsignedInteger(this.bitSize, value);
    }

    private getValueRange(): Range {
      const maxValue = (Math.pow(2, this.bitSize)) - 1;

      return Range.fromTo(0, maxValue);
    }
  };

  private constructor(
      private readonly bitSize: number, private readonly value: number) {}

  public getValue(): number {
    return this.value;
  }
}
