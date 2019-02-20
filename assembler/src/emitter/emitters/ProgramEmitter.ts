import { ClassObject } from "../../language/domain/ClassObject";
import { GlobalsContext } from "../../language/domain/GlobalFunctionContext";
import { Program } from "../../language/domain/Program";
import { IEmitter } from "../IEmitter";
import { IWriter } from "../IWriter";
import { BufferedWriter } from "../writers/BufferedWriter";
import { ClassObjectEmitter } from "./ClassObjectEmitter";
import { GlobalsEmitter } from "./GlobalsEmitter";

export class ProgramEmitter implements IEmitter<Program> {

  public static for(program: Program) {
    const writer = new BufferedWriter(program.getTotalSize());

    return new ProgramEmitter(writer);
  }

  private readonly classEmitter: IEmitter<ClassObject[]>;
  private readonly globalsEmitter: IEmitter<GlobalsContext>;

  private constructor(
    private readonly writer: IWriter,
  ) {
    this.classEmitter = new ClassObjectEmitter();
    this.globalsEmitter = new GlobalsEmitter();
  }

  public emit(program: Program, writer: IWriter): void {
    this.classEmitter.emit(program.getClasses(), writer);
    this.globalsEmitter.emit(program.getGlobals(), writer);
  }

}
