from typing import List

from assembler.chars import Chars
from assembler.instructionparser import InstructionParser
from assembler.lexeme import Lexeme, LexemeType
from assembler.linetokenizer import LineTokenizer
from assembler.metainstructionparser import MetaInstructionParser


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

    def __parse_line(self, lexemes: List[Lexeme]):
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

    def __is_line_meta(self, lexemes: List[Lexeme]):
        if len(lexemes) == 0:
            return False

        return lexemes[0].is_type(LexemeType.META_START)
