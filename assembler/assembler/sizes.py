from assembler.size import Size


class Sizes:
    UINT = Size.from_bytes(2)
    INT = Size.from_bytes(2)
    REFERENCE = Size.from_bytes(4)
    FLOAT = Size.from_bytes(4)
    OPCODE = Size.from_bytes(1)
