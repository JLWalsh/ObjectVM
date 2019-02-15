
export enum ArgumentType {
  INT,
  UINT,
  FLOAT,
  STRING,
  CLASS_REF,
  FUNC_REF,
  STATIC_FUNC_REF,
}

export class Argument {

  constructor(
    private readonly type: ArgumentType,
    private readonly value: any,
  ) {}

  public getValue(): any {
    return this.value;
  }
}
