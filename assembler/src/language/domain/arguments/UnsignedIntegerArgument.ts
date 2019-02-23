import {Numbers} from "../../math/Numbers";
import {Size} from "../../math/Size";
import {IArgument, IArgumentVisitor} from "../Argument";
import {NumericOutOfRangeError} from "../errors/NumericOutOfRangeError";
import {UnsignedInteger} from "../UnsignedInteger";

export class UnsignedIntegerArgument implements IArgument<UnsignedInteger> {

    constructor(private readonly unsignedInteger: UnsignedInteger) {}

    public accept(visitor: IArgumentVisitor): void {
        visitor.visitUnsignedInteger(this.unsignedInteger);
    }

    public getSize(): Size {
        return this.unsignedInteger.getSize();
    }

}
