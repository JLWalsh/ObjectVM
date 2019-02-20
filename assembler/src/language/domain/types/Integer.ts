import {Range} from "../../../math/Range";
import {Size} from "../../math/Size";
import {NumericOutOfRangeError} from "../errors/NumericOutOfRangeError";
import {INumeric} from "../Numeric";

export class Integer implements INumeric {

  public static withSize(size: Size) {
    return new Integer.Builder(size);
  }

  private static Builder = class Builder {
    constructor(private readonly size: Size) {}

    public createWithValue(value: number) {
      const range = this.getValueRange();
      if (!range.contains(value)) {
        throw new NumericOutOfRangeError(value, range);
      }

      return new Integer(this.size, value);
    }

    private getValueRange(): Range {
      const maxValue = (Math.pow(2, this.size.toBytes())) / 2;
      const minValue = -(maxValue - 1);

      return Range.fromTo(minValue, maxValue);
    }
  };

  private constructor(
      private readonly size: Size, private readonly value: number) {}

  public asNumber(): number {
    return this.value;
  }

  public getSize(): Size {
    return this.size;
  }
}
