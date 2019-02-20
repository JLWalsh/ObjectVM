import { Argument } from "../../language/domain/Argument";
import { IEmitter } from "../IEmitter";
import { IWriter } from "../IWriter";
import {ArgumentEmitterVisitorBuilder} from "./ArgumentEmitterVisitor";

export abstract class ArgumentEmitter implements IEmitter<Argument[]> {

  constructor(
    private readonly argumentEmitterVisitorBuilder: ArgumentEmitterVisitorBuilder,
  ) {}

  public emit(args: Argument[], writer: IWriter): void {
    const visitor = this.argumentEmitterVisitorBuilder.buildWithWriter(writer);

    args.forEach((arg) => {
      arg.accept(visitor);
    });
  }

}
