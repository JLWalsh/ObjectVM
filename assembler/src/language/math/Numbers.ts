import {Range} from "../../math/Range";
import {Size} from "./Size";

export class Numbers {

    public static signedRange(size: Size): Range {
        const maxValue = (Math.pow(2, size.toBytes())) / 2;
        const minValue = -(maxValue - 1);

        return Range.fromTo(minValue, maxValue);
    }

    public static unsignedRange(size: Size): Range {
        const maxValue = (Math.pow(2, size.toBytes())) - 1;

        return Range.fromTo(0, maxValue);
    }
}
