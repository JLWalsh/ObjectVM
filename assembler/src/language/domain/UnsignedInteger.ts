import {Size} from "../math/Size";
import {Numbers} from "../math/Numbers";
import {NumericOutOfRangeError} from "./errors/NumericOutOfRangeError";

export class UnsignedInteger {

    public static withSize(size: Size) {
        return new UnsignedInteger.Builder(size);
    }

    private static Builder = class Builder {
        constructor(private readonly size: Size) {}

        public createWithValue(value: number) {
            const range = Numbers.unsignedRange(this.size);
            if (!range.contains(value)) {
                throw new NumericOutOfRangeError(value, range);
            }

            return new UnsignedInteger(this.size, value);
        }
    };

    private constructor(
        private readonly size: Size, private readonly value: number) {}

    public getSize(): Size {
        return this.size;
    }
}
