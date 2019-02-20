import { Argument, IArgumentVisitor } from "../../language/domain/Argument";
import { Integer } from "../../language/domain/Integer";
import { IEmitter } from "../IEmitter";
import { IWriter } from "../IWriter";

export interface IArgumentEmitters {
    integerEmitter: IEmitter<Integer>;
}

export class ArgumentEmitterVisitorBuilder {

    public static usingEmitters(emitters: IArgumentEmitters): ArgumentEmitterVisitorBuilder {
        return new ArgumentEmitterVisitorBuilder(emitters);
    }

    private constructor(
        private readonly emitters: IArgumentEmitters,
    ) {}

    public buildWithWriter(writer: IWriter): ArgumentEmitterVisitor {
        return new ArgumentEmitterVisitor(writer, this.emitters);
    }
}

export class ArgumentEmitterVisitor implements IArgumentVisitor {

    constructor(
        private readonly writer: IWriter,
        private readonly emitters: IArgumentEmitters,
    ) {}

    public visitInteger(integer: Integer): void {
        // TODO visit the integer!
    }
}
