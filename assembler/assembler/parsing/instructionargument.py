from enum import Enum

from assembler.size import Size
from assembler.sizes import Sizes


class InstructionArgumentType(Enum):
    UINT = 0
    INT = 1
    FUNCTION_SIGNATURE = 2
    STATIC_FUNCTION_SIGNATURE = 3
    STRING = 4
    FLOAT = 5
    CLASS_SIGNATURE = 6


class InstructionArgument:

    def __init__(self, type: InstructionArgumentType, size: Size):
        self.type = type
        self.size = size

    @staticmethod
    def uint() -> 'InstructionArgument':
        return InstructionArgument(InstructionArgumentType.UINT, Sizes.UINT)

    @staticmethod
    def int() -> 'InstructionArgument':
        return InstructionArgument(InstructionArgumentType.INT, Sizes.INT)

    @staticmethod
    def function_signature() -> 'InstructionArgument':
        return InstructionArgument(InstructionArgumentType.FUNCTION_SIGNATURE,
                                   Sizes.UINT + Sizes.UINT)  # class id + method id

    @staticmethod
    def static_function_signature() -> 'InstructionArgument':
        return InstructionArgument(InstructionArgumentType.STATIC_FUNCTION_SIGNATURE, Sizes.UINT)  # method id

    @staticmethod
    def string() -> 'InstructionArgument':
        return InstructionArgument(InstructionArgumentType.STRING, Sizes.REFERENCE)

    @staticmethod
    def float() -> 'InstructionArgument':
        return InstructionArgument(InstructionArgumentType.FLOAT, Sizes.FLOAT)

    @staticmethod
    def class_signature() -> 'InstructionArgument':
        return InstructionArgument(InstructionArgumentType.CLASS_SIGNATURE, Sizes.UINT)  # class id
