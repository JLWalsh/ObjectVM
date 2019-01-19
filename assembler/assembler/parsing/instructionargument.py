from enum import Enum


class InstructionArgument(Enum):
    UINT = 0
    FUNCTION_SIGNATURE = 1
    STATIC_FUNCTION_SIGNATURE = 2
    FLOAT = 3
    INT = 4
    STRING = 5
    CLASS_SIGNATURE = 6
