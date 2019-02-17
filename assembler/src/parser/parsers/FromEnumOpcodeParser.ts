import {Opcode} from '../../language/domain/Opcode';
import {IKeywordParser} from '../IKeywordParser';

export class FromEnumOpcodeParser implements IKeywordParser<Opcode> {
  public parse(value: string): Opcode {
    return Opcode[value as keyof typeof Opcode];
  }
}
