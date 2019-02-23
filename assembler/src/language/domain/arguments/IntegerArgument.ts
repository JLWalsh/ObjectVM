import {Size} from "../../math/Size";
import {IArgument, IArgumentVisitor} from "../Argument";
import {Integer} from "../Integer";

export class IntegerArgument implements IArgument<Integer> {

    constructor(private readonly integer: Integer) {}

    public accept(visitor: IArgumentVisitor): void {
        visitor.visitInteger(this.integer);
    }

    public getSize(): Size {
        return this.integer.getSize();
    }

}
