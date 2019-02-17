import { IWriter } from "../IWriter";

export class BufferedWriter implements IWriter {

  private readonly buffer: ArrayBuffer;
  private readonly dataView: DataView;
  private bytePosition: number;

  constructor(numberOfBytes: number) {
    this.buffer = new ArrayBuffer(numberOfBytes);
    this.dataView = new DataView(this.buffer);
    this.bytePosition = 0;
  }

  public finish(): Uint8Array {
    return new Uint8Array(this.buffer);
  }

  public write(bytes: number[]): void {
    if (this.isAtEnd()) {
      throw new Error("Illegal state: attempted to write more items than available in buffer");
    }

    bytes.forEach((byte) => {
      this.dataView.setUint8(this.bytePosition++, byte);
    });
  }

  private isAtEnd(): boolean {
    return this.bytePosition >= this.buffer.byteLength;
  }
}
