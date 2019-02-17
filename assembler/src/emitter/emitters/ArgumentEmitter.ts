import { Argument } from "../../language/domain/Argument";
import { IEmitter } from "../IEmitter";
import { IWriter } from "../IWriter";

export class ArgumentEmitter implements IEmitter<Argument[]> {

  public emit(args: Argument[], writer: IWriter): void {
  }

}
