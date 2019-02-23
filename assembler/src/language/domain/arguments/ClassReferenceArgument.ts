import {Size} from "../../math/Size";
import {Argument, ArgumentType, IArgumentVisitor} from "../Argument";

export class ClassReferenceArgument extends Argument {

    constructor(
        private readonly classReference: string,
    ) {
        super(ArgumentType.CLASS_REF);
    }

    public accept(visitor: IArgumentVisitor): void {
        visitor.visitClassReference(this);
    }

    public getSize(): Size {
        return undefined;
    }

    public getValue(): any {
    }

}
