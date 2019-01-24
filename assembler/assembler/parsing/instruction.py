from typing import List

from assembler.opcode import Opcode
from assembler.parsing.instructionargument import InstructionArgument
from assembler.size import Size
from assembler.sizes import Sizes


class ParsedInstruction:

    def __init__(self, opcode: Opcode, size: Size, args: List[any]):
        self.opcode = opcode
        self.size = size
        self.args = args

    def __str__(self):
        str_val = f'{self.opcode.name}: '
        for arg in self.args:
            str_val += str(arg)

        return str_val


class Instruction:

    def __init__(self, opcode: Opcode, args: List[InstructionArgument] = None):
        if args is None:
            args = []

        self.opcode = opcode
        self.args = args
        self.size = self.__calculate_bytecode_size(args)

    def bytecode_size(self) -> Size:
        return self.size

    def __calculate_bytecode_size(self, args: List[InstructionArgument]) -> Size:
        size = Sizes.OPCODE
        for arg in args:
            size += arg.size

        return size
