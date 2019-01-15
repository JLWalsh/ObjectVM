from enum import Enum


class Opcode(Enum):
    HALT = 0,
    NEW = 1,
    INVOKE_STATIC = 2,
    INVOKE_VIRTUAL = 3,
    RETURN_VOID = 4,
    RETURN = 5,
    UI_PUSH = 6,
    UI_PRINT = 7,
    UI_GLOBAL_STORE = 8,
    UI_GLOBAL_LOAD = 9,
    LOCAL_LOAD = 10,
    DUP = 11,
