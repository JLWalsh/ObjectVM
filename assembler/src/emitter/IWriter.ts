
export interface IWriter {
  write(bytes: number[]): void;
  finish(): Uint8Array;
}
