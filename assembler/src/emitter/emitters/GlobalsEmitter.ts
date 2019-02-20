import {StaticFunction} from "../../language/domain/Function";
import { GlobalsContext } from "../../language/domain/GlobalFunctionContext";
import { IEmitter } from "../IEmitter";
import { IWriter } from "../IWriter";

export class GlobalsEmitter implements IEmitter<GlobalsContext> {

  constructor(
      private readonly functionEmitter: IEmitter<StaticFunction>,
  ) {}

  public emit(globals: GlobalsContext, writer: IWriter): void {
    globals.getGlobalFunctions().forEach((func) => this.functionEmitter.emit(func, writer));
  }

}
