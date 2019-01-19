from typing import List

from assembler.parsing.instructionargument import InstructionArgument
from assembler.opcode import Opcode


class ParsedInstruction:

    def __init__(self, opcode: Opcode, args: List[any]):
        self.opcode = opcode
        self.args = args

    def __str__(self):
        str_val = f'{self.opcode.name}: '
        for arg in self.args:
            str_val += str(arg)

        return str_val


class Instruction:

    def __init__(self, opcode: Opcode, arg_types: List[InstructionArgument] = None):
        if arg_types is None:
            arg_types = []

        self.opcode = opcode
        self.args = arg_types
