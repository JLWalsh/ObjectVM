from typing import List

from assembler.parsing.chars import Chars
from assembler.parsing.instructionparser import InstructionParser
from assembler.parsing.token import Token, TokenType
from assembler.parsing.linetokenizer import LineTokenizer
from assembler.parsing.metainstructionparser import MetaInstructionParser


class ParseError:

    def __init__(self, message, line=None):
        self.message = message
        self.line = line

    def __str__(self):
        return f"[{self.line}]: {self.message}."


class Parser:

    def __init__(self, source: str):
        self.source = source
        self.errors = []
        self.line = None

    def parse(self):
        lines = self.source.split(Chars.NEWLINE.value)

        return self.__parse_lines(lines)

    def get_errors(self):
        return self.errors

    def __parse_lines(self, lines: List[str]):
        parsed_lines = []

        for index, line in enumerate(lines):
            self.line = index

            try:
                lexemes = LineTokenizer(line).tokenize()

                parsed_line = self.__parse_line(lexemes)

                if parsed_line is not None:
                    parsed_lines.append(parsed_line)
            except Exception as e:
                self.__append_error(e)

        return parsed_lines

    def __parse_line(self, lexemes: List[Token]):
        if len(lexemes) == 0:
            return None

        try:
            if self.__is_line_meta(lexemes):
                return MetaInstructionParser(lexemes).parse()
            else:
                return InstructionParser.with_default_instructions(lexemes).parse()
        except Exception as e:
            self.__append_error(e)

    def __append_error(self, error: Exception):
        parse_error = ParseError(error, self.line + 1)
        self.errors.append(parse_error)

    def __is_line_meta(self, lexemes: List[Token]):
        if len(lexemes) == 0:
            return False

        return lexemes[0].is_type(TokenType.META_START)
