from enum import Enum


class InstructionArgumentType(Enum):
    UINT = 0
    FUNC_REF = 1
    STATIC_FUNC_REF = 2
    PTR = 3
