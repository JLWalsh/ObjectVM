from typing import List

from type import Type


class Instruction:

    def __init__(self, literal: str, opcode_id: int, args: List[Type]):
        self.literal = literal
        self.opcode_id = opcode_id
        self.args = args
