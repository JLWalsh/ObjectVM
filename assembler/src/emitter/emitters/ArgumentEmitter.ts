import { Argument, IArgumentVisitor } from "../../language/domain/Argument";
import { Integer } from "../../language/domain/Integer";
import { IEmitter } from "../IEmitter";
import { IWriter } from "../IWriter";

class ArgumentEmitterVisitor implements IArgumentVisitor {

  private writer?: IWriter;

  constructor(
    private readonly integerEmitter: IEmitter<Integer>,
  ) {}

  public writeTo(writer: IWriter) {
    this.writer = writer;
  }

  public visitStuff(stuff: Argument): void {
    throw new Error("Method not implemented.");
  }
}

export abstract class ArgumentEmitter implements IEmitter<Argument[]> {

  constructor(
    private readonly argumentEmitterVisitor: ArgumentEmitterVisitor,
  ) {}

  public emit(args: Argument[], writer: IWriter): void {
    this.argumentEmitterVisitor.writeTo(writer);
    args.forEach((arg) => {
      arg.accept(this.argumentEmitterVisitor);
    });
  }

}
