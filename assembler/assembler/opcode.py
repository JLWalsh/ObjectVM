from enum import Enum


class Opcode(Enum):
    HALT = 1,
    NEW = 2,
    INVOKE_STATIC = 3,
    INVOKE_VIRTUAL = 4,
    RETURN_VOID = 5,
    RETURN = 6,
    UI_PUSH = 7,
    UI_PRINT = 8,
    UI_GLOBAL_STORE = 9,
    UI_GLOBAL_LOAD = 10,
    LOCAL_LOAD = 11,
    DUP = 12,
