
export class ByteArray {

    public static fromArrayBuffer(buffer: ArrayBuffer) {
        const array = new Uint8Array(buffer);

        return new ByteArray(array);
    }

    private constructor(private readonly bytes: Uint8Array) {}

    public asUint8Array(): Uint8Array {
        return this.bytes;
    }
}
