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