from typing import List

from assembler.opcode import Opcode
from assembler.type import Type


class Instruction:

    def __init__(self, opcode: Opcode, args: List[Type] = []):
        self.opcode = opcode
        self.args = args
