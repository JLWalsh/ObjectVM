from typing import List

from assembler.opcode import Opcode
from assembler.instructionargument import InstructionArgumentType


class Instruction:

    def __init__(self, opcode: Opcode, args: List[InstructionArgumentType] = []):
        self.opcode = opcode
        self.args = args
