
export enum MetaInstructionType {
  CLASS_DECLARATION = "class",
  FUNCTION_DECLARATION = "function",
  MEMSIZE_MODIFIER = "memsize",
}

export class MetaInstruction {

  constructor(
    private readonly type: MetaInstructionType,
  ) {}
}
