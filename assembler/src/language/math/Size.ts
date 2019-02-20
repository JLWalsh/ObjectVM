
export class Size {

    public static ZERO = Size.fromBytes(0);

    public static fromBytes(bytes: number): Size {
       return new Size(bytes);
    }

    private constructor(
        private readonly bytes: number,
    ) {}

    public addWith(size: Size): Size {
        return Size.fromBytes(this.bytes + size.bytes);
    }

    public toBytes(): number {
        return this.bytes;
    }
}
