import {INumeric} from "./Numeric";
import {Size} from "../math/Size";
import {Numbers} from "../math/Numbers";
import {NumericOutOfRangeError} from "./errors/NumericOutOfRangeError";

export class Integer implements INumeric {

    public static withSize(size: Size) {
        return new Integer.Builder(size);
    }

    private static Builder = class Builder {
        constructor(private readonly size: Size) {}

        public createWithValue(value: number) {
            const range = Numbers.signedRange(this.size);
            if (!range.contains(value)) {
                throw new NumericOutOfRangeError(value, range);
            }

            return new Integer(this.size, value);
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
