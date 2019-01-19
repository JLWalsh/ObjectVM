from typing import List, Optional

from assembler.float import Float
from assembler.funcref import FuncRef
from assembler.parsing.instruction import Instruction, ParsedInstruction
from assembler.parsing.instructionargument import InstructionArgument
from assembler.int import UInt, Int
from assembler.parsing.token import Token, TokenType
from assembler.opcode import Opcode


class OpcodeParser:

    @staticmethod
    def parse(raw_opcode: str) -> Optional[Opcode]:
        for opcode in Opcode:
            if opcode.value == raw_opcode:
                return opcode

        return None


class InstructionParser:

    def __init__(self, instructions: List[Instruction], lexemes: List[Token]):
        self.instructions = instructions
        self.lexemes = lexemes
        self.position = 0
        self.args = []

    def parse(self) -> ParsedInstruction:
        opcode = self.__match_lexeme(TokenType.WORD)
        if not opcode:
            raise ValueError('First keyword must be an opcode (word)')

        instruction = self.__find_matching_instruction_for(opcode.parsed_value)
        if not instruction:
            raise ValueError(f'Unrecognized opcode: {opcode.parsed_value}')

        for arg in instruction.args:
            if arg == InstructionArgument.FUNCTION_SIGNATURE:
                self.__parse_func_ref()
            elif arg == InstructionArgument.STATIC_FUNCTION_SIGNATURE:
                self.__parse_static_func_ref()
            elif arg == InstructionArgument.UINT:
                self.__parse_uint()
            elif arg == InstructionArgument.INT:
                self.__parse_int()
            elif arg == InstructionArgument.STRING:
                self.__parse_str()
            elif arg == InstructionArgument.FLOAT:
                self.__parse_float()
            elif arg == InstructionArgument.CLASS_SIGNATURE:
                self.__parse_class_ref()
            else:
                raise NotImplementedError(f'Argument type {arg.value} has no parser')

        if not self.__is_at_end():
            raise ValueError(f'Too many arguments supplied for opcode {instruction.opcode.value}')

        return ParsedInstruction(instruction.opcode, self.args)

    def __parse_class_ref(self):
        class_name = self.__match_lexeme(TokenType.WORD)
        if not class_name:
            raise ValueError('Expected class name')

        self.args.append(class_name.parsed_value)

    def __parse_str(self):
        str = self.__match_lexeme(TokenType.STRING)
        if not str:
            raise ValueError('Expected string')

        self.args.append(str.parsed_value)

    def __parse_int(self):
        int = self.__match_lexeme(TokenType.INT)
        if not int:
            raise ValueError('Expected numeric value (int)')

        if not Int.default().can_hold(int.parsed_value):
            raise ValueError(f'Int cannot represent {int}')

        self.args.append(int.parsed_value)

    def __parse_uint(self):
        uint = self.__match_lexeme(TokenType.INT)
        if not uint:
            raise ValueError('Expected unsigned numeric value (uint)')

        if not UInt.default().can_hold(uint.parsed_value):
            raise ValueError(f'UInt cannot represent {uint.parsed_value}')

        self.args.append(uint.parsed_value)

    def __parse_float(self):
        flt = self.__match_lexeme(TokenType.FLOAT)
        if not flt:
            raise ValueError('Expected float value')

        if not Float.default().can_hold(flt.parsed_value):
            raise ValueError(f'Float cannot represent {flt.parsed_value}')

        self.args.append(flt.parsed_value)

    def __parse_func_ref(self):
        class_name = self.__match_lexeme(TokenType.WORD)
        if not class_name:
            raise ValueError('Function reference lacks class name')

        if not self.__match_lexeme(TokenType.QUOTE_BLOCK):
            raise ValueError('Function reference lacks ::')

        func_name = self.__match_lexeme(TokenType.WORD)
        if not func_name:
            raise ValueError('Function lacks name')

        func_ref = FuncRef(func_name.parsed_value, class_name.parsed_value)
        self.args.append(func_ref)

    def __parse_static_func_ref(self):
        first_name = self.__match_lexeme(TokenType.WORD)
        if not first_name:
            raise ValueError('Static function reference lacks class name or function name')

        if not self.__match_lexeme(TokenType.QUOTE_BLOCK):
            func_ref = FuncRef(first_name.parsed_value)
            self.args.append(func_ref)

            return

        func_name = self.__match_lexeme(TokenType.WORD)
        if not func_name:
            raise ValueError('Function lacks name')

        func_ref = FuncRef(first_name.parsed_value, func_name.parsed_value)
        self.args.append(func_ref)

    def __find_matching_instruction_for(self, opcode_str: str) -> Optional[Instruction]:
        for instruction in self.instructions:
            # <rant salty class="toFix">Apparently python can't compare strings for shit</rant>
            if opcode_str.__eq__(instruction.opcode.name):
                return instruction

        return None

    def __peek(self) -> Optional[Token]:
        if self.__is_at_end():
            return None

        return self.lexemes[self.position]

    def __match_lexeme(self, type: TokenType):
        value = self.__peek()
        if not value:
            return False

        if value.is_type(type):
            self.position += 1
            return value

        return False

    def __is_at_end(self):
        return self.position >= len(self.lexemes)

    @staticmethod
    def with_default_instructions(lexemes: List[Token]):
        instructions = [
            Instruction(Opcode.HALT),
            Instruction(Opcode.NEW, [InstructionArgument.CLASS_SIGNATURE]),
            Instruction(Opcode.INVOKE_STATIC, [InstructionArgument.STATIC_FUNCTION_SIGNATURE]),
            Instruction(Opcode.INVOKE_VIRTUAL,
                        [InstructionArgument.FUNCTION_SIGNATURE]),
            Instruction(Opcode.RETURN_VOID),
            Instruction(Opcode.RETURN),
            Instruction(Opcode.UI_PUSH, [InstructionArgument.UINT]),
            Instruction(Opcode.UI_PRINT),
            Instruction(Opcode.UI_GLOBAL_STORE, [InstructionArgument.UINT]),
            Instruction(Opcode.UI_GLOBAL_LOAD, [InstructionArgument.UINT]),
            Instruction(Opcode.LOCAL_LOAD, [InstructionArgument.UINT]),
            Instruction(Opcode.DUP)
        ]

        return InstructionParser(instructions, lexemes)
