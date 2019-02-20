import {ByteArray} from "./ByteArray";

export interface IWriter {
  write(bytes: number[]): void;
  finish(): ByteArray;
  getBytePosition(): number;
}
