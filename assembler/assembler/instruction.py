from typing import List

from assembler.instructionargument import InstructionArgument
from assembler.opcode import Opcode


class ParsedInstruction:

    def __init__(self, opcode: Opcode, args: List[any]):
        self.opcode = opcode
        self.args = args


class Instruction:

    def __init__(self, opcode: Opcode, arg_types: List[InstructionArgument] = None):
        if arg_types is None:
            arg_types = []

        self.opcode = opcode
        self.args = arg_types
