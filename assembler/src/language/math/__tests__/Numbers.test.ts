import {Range} from "../../../math/Range";
import {Numbers} from "../Numbers";
import {Size} from "../Size";

describe("Numbers", () => {
    describe("given signed number", () => {
        const SIZE = Size.fromBytes(8);
        const MAX_VALUE_FOR_SIZE = 128;
        const MIN_VALUE_FOR_SIZE = -127;

        it("should calculate signed range", () => {
            const expectedRange = Range.fromTo(MIN_VALUE_FOR_SIZE, MAX_VALUE_FOR_SIZE);

            const range = Numbers.signedRange(SIZE);

            expect(range).toEqual(expectedRange);
        });
    });

    describe("given unsigned number", () => {
        const SIZE = Size.fromBytes(16);
        const MIN_VALUE_FOR_SIZE = 0;
        const MAX_VALUE_FOR_SIZE = 65535;

        it("should calculate unsigned range", () => {
            const expectedRange = Range.fromTo(MIN_VALUE_FOR_SIZE, MAX_VALUE_FOR_SIZE);

            const range = Numbers.unsignedRange(SIZE);

            expect(range).toEqual(expectedRange);
        });
    });
});
