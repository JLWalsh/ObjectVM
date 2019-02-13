import { MetaInstructionType } from "../../language/MetaInstruction";
import { IKeywordParser } from "../IKeywordParser";

export class FromEnumMetaInstructionTypeParser implements IKeywordParser<MetaInstructionType> {

  public parse(value: string): void | MetaInstructionType {
    return MetaInstructionType[value as keyof typeof MetaInstructionType];
  }
}
