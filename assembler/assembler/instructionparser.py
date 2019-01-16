from typing import List

from assembler.instruction import Instruction
from assembler.lexeme import Lexeme, LexemeType
from assembler.opcode import Opcode
from assembler.instructionargument import InstructionArgumentType


class OpcodeParser:

    @staticmethod
    def parse(raw_opcode: str) -> Opcode | None:
        for opcode in Opcode:
            if opcode.value == raw_opcode:
                return opcode

        return None


class InstructionParser:

    def __init__(self, instructions: List[Instruction], lexemes: List[Lexeme]):
        self.instructions = instructions
        self.lexemes = lexemes
        self.position = 0

    def parse(self):
        opcode = self.__match_lexeme(LexemeType.WORD)
        if not opcode:
            raise ValueError('First keyword must be an opcode (word)')

        self.__validate__instruction_usage(opcode)

    def __validate__instruction_usage(self, opcode: Opcode):
        instruction = self.__find_matching_instruction_for(opcode)

        if len(self.lexemes) - 1 > len(instruction.args):
            raise ValueError(f'Too many arguments provided for instruction {instruction.opcode.value}')

        if len(self.lexemes) - 1 < len(instruction.args):
            raise ValueError(f'Too few arguments provided for instruction {instruction.opcode.value}')

        arg_offset = 1
        for arg_index, arg_type in enumerate(instruction.args):
            if self.lexemes[arg_offset + arg_index].lexeme_type

    def __map_lexeme_to_type(self, lexeme: Lexeme) -> InstructionArgumentType:
        if lexeme.lexeme_type == LexemeType.INTEGER:


    def __find_matching_instruction_for(self, opcode: Opcode) -> Instruction | None:
        for instruction in self.instructions:
            if instruction.opcode == opcode:
                return instruction

        return None

    def __peek(self):
        if self.__is_at_end():
            return None

        return self.lexemes[self.position]

    def __match_lexeme(self, type: LexemeType):
        value = self.__peek()

        if value.lexeme_type == type:
            self.position += 1
            return value

        return False

    def __is_at_end(self):
        return self.position >= len(self.lexemes)

    @staticmethod
    def with_default_instructions(lexemes: List[Lexeme]):
        instructions = [
            Instruction(Opcode.HALT),
            Instruction(Opcode.NEW, [InstructionArgumentType.UINT]),
            Instruction(Opcode.INVOKE_STATIC, [InstructionArgumentType.UINT, InstructionArgumentType.UINT]),
            Instruction(Opcode.INVOKE_VIRTUAL, [InstructionArgumentType.UINT, InstructionArgumentType.UINT, InstructionArgumentType.UINT]),
            Instruction(Opcode.RETURN_VOID),
            Instruction(Opcode.RETURN),
            Instruction(Opcode.UI_PUSH, [InstructionArgumentType.UINT]),
            Instruction(Opcode.UI_PRINT),
            Instruction(Opcode.UI_GLOBAL_STORE, [InstructionArgumentType.UINT]),
            Instruction(Opcode.UI_GLOBAL_LOAD, [InstructionArgumentType.UINT]),
            Instruction(Opcode.LOCAL_LOAD, [InstructionArgumentType.UINT]),
            Instruction(Opcode.DUP)
        ]

        return InstructionParser(instructions, lexemes)
