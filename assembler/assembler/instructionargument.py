from enum import Enum


class InstructionArgument(Enum):
    UINT = 0
    FUNC_REF = 1
    STATIC_FUNC_REF = 2
    FLOAT = 3
    INT = 4
    STR = 5
