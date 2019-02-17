import { GlobalsContext } from "../../language/domain/GlobalFunctionContext";
import { IEmitter } from "../IEmitter";
import { IWriter } from "../IWriter";

export class GlobalsEmitter implements IEmitter<GlobalsContext> {
  public emit(value: GlobalsContext, writer: IWriter): void {
    throw new Error("Method not implemented.");
  }

}
