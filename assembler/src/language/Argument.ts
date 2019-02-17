import {Integer} from './domain/Integer';

export enum ArgumentType {
  INT,
  UINT,
  FLOAT,
  STRING,
  CLASS_REF,
  FUNC_REF,
  STATIC_FUNC_REF,
}

export abstract class Argument {
  protected constructor(
      private readonly type: ArgumentType,
  ) {}

  public getType(): ArgumentType {
    return this.type;
  }

  public abstract getValue(): any;

  public abstract getSize(): number;
}

class IntArgument extends Argument {
  constructor(private readonly value: Integer) {
    super(ArgumentType.INT);
  }

  public getValue() {
    return this.value;
  }

  public getSize(): number {
    return this.value.getSize();
  }
}