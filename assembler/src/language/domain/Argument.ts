import {Size} from "../math/Size";
import {Integer} from "./types/Integer";

export enum ArgumentType {
  INT,
  UINT,
  FLOAT,
  STRING,
  CLASS_REF,
  FUNC_REF,
  STATIC_FUNC_REF,
}

export interface IArgumentVisitor {
  visitInteger(stuff: Integer): void;
}

export abstract class Argument {
  protected constructor(
      private readonly type: ArgumentType,
  ) {}

  public getType(): ArgumentType {
    return this.type;
  }

  public abstract getValue(): any;

  public abstract getSize(): Size;

  public abstract accept(visitor: IArgumentVisitor): void;
}
