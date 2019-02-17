import { ClassObject } from "../../language/domain/ClassObject";
import { StaticFunction } from "../../language/domain/Function";
import { IEmitter } from "../IEmitter";
import { IWriter } from "../IWriter";

export class ClassObjectEmitter implements IEmitter<ClassObject[]> {

  constructor(
    private readonly functionEmitter: IEmitter<StaticFunction>,
  ) {}

  public emit(classes: ClassObject[], writer: IWriter): void {
    classes.forEach((c) => {
      c.getFunctions().forEach((func) => {
        this.functionEmitter.emit(func, writer);
      });
    });
  }
}
