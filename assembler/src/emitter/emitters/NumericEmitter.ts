import {INumeric} from "../../language/domain/Numeric";
import {IEmitter} from "../IEmitter";
import {IWriter} from "../IWriter";
import {NumericSerialiser} from "../serialisers/NumericSerialiser";

export class NumericEmitter implements IEmitter<INumeric> {

    constructor(
        private readonly numericSerialiser: NumericSerialiser,
    ) {}

    public emit(value: INumeric, writer: IWriter): void {
        const bytes = this.numericSerialiser.serialiseToBytes(value);

        writer.write(bytes);
    }

}
