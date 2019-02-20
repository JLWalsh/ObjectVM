import { ClassObject } from "./ClassObject";
import { GlobalsContext } from "./GlobalFunctionContext";

export class Program {

  constructor(
    private readonly classes: ClassObject[],
    private readonly globals: GlobalsContext,
  ) {}

  public getClasses(): ClassObject[] {
    return this.classes;
  }

  public getGlobals(): GlobalsContext {
    return this.globals;
  }

  public getTotalSize(): number {
    const classesSize = this.classes.reduce((size, objectClass) => size + objectClass.getSize(), 0);
    
    return classesSize + this.globals.getSize();
  }
}
