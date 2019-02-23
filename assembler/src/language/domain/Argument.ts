import {Size} from "../math/Size";
import {IntegerArgument} from "./arguments/IntegerArgument";
import {ClassReferenceArgument} from "./arguments/ClassReferenceArgument";
import {Integer} from "./Integer";
import {UnsignedInteger} from "./UnsignedInteger";

export enum ArgumentType {
  INT,
  UINT,
  FLOAT,
  STRING,
  CLASS_REF,
  FUNC_REF,
  STATIC_FUNC_REF,
}

export type PossibleArgumentTypes = Integer | ClassReferenceArgument | UnsignedInteger;

export interface IArgumentVisitor {
  visitInteger(argument: Integer): void;
  visitUnsignedInteger(argument: UnsignedInteger): void;
  visitClassReference(argument: ClassReferenceArgument): void;
}

export interface IArgument<T extends PossibleArgumentTypes> {
  getSize(): Size;
  accept(visitor: IArgumentVisitor): void;
}
