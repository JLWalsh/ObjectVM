import {Size} from "../math/Size";
import {StaticFunction} from "./Function";

export class GlobalsContext {

  constructor(
      private readonly globalFunctions: StaticFunction[],
  ) {}

  public getSize(): Size {
    return this.globalFunctions.reduce((size, func) => size.addWith(func.getSize()), Size.ZERO);
  }

  public getGlobalFunctions(): StaticFunction[] {
    return this.globalFunctions;
  }
}
