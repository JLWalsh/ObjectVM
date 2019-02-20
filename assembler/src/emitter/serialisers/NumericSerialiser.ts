import {INumeric} from "../../language/domain/Numeric";

export enum Endianess {
    BIG_ENDIAN,
}

export class NumericSerialiser {

    public static bigEndian(): NumericSerialiser {
        return new NumericSerialiser(Endianess.BIG_ENDIAN);
    }

    private constructor(
        private readonly endianess: Endianess,
    ) {}

    public serialiseToBytes(numeric: INumeric): number[] {
        return [];
    }
}
