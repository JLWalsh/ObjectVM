import { IWriter } from "./IWriter";

export interface IEmitter<T> {
  emit(value: T, writer: IWriter): void;
}
