from typing import List

from char import Char
from instruction import Instruction
from token import Token, TokenType
from tokenassembler import TokenAssembler
from chars import Chars


class LineParser:

    def __init__(self, line: str):
        self.line = line
        self.position = 0
        self.last_parse_start = 0
        self.tokens = []

    def parse(self):
        while not self.__is_at_end():
            self.last_parse_start = self.position

            char = self.__advance()

            if Char.is_numeric(char):
                self.__parse_numeric()
            elif Char.is_alpha(char):
                self.__parse_word()
            elif char == Chars.STRING.value:
                self.__parse_string()
            elif char == Chars.WHITESPACE.value:
                continue
            elif char == Chars.COMMENT.value and self.__peek() == Chars.COMMENT.value:
                break
            else:
                raise ValueError(f"Unrecognized character: {char}")

        return self.tokens

    def __parse_numeric(self):
        while not self.__is_at_end() and Char.is_numeric(self.__peek()):
            self.__advance()

        if self.__peek() == Chars.DOT.value:
            return self.__continue_parse_float()

        literal = self.__extract_literal()
        token = TokenAssembler.assemble_integer(literal)

        self.tokens.append(token)

    def __continue_parse_float(self):
        self.__advance()  # Skip the dot

        while not self.__is_at_end() and Char.is_numeric(self.__peek()):
            self.__advance()

        literal = self.__extract_literal()
        token = TokenAssembler.assemble_float(literal)

        self.tokens.append(token)

    def __parse_word(self):
        while not self.__is_at_end() and Char.is_alpha(self.__peek()):
            self.__advance()

        literal = self.__extract_literal()
        token = Token(TokenType.WORD, literal, literal)

        self.tokens.append(token)

    def __parse_string(self):
        string = ''

        while not self.__is_at_end() and self.__peek() != Chars.STRING.value:
            string += self.__advance()

            if self.__peek() == Chars.ESCAPE_STRING.value:
                self.__advance()            # Skip escape character
                string += self.__advance()  # Skip over escaped value

        if self.__peek() != Chars.STRING.value:
            raise ValueError("Unterminated string")

        self.__advance()  # Consume the quote at end of string

        literal = self.__extract_literal()
        token = Token(TokenType.STRING, string, literal)

        self.tokens.append(token)

    def __peek(self):
        if self.__is_at_end():
            return None

        return self.line[self.position]

    def __advance(self) -> chr:
        char = self.__peek()
        self.position += 1

        return char

    def __extract_literal(self):
        literal_start = self.line[self.last_parse_start:]

        return literal_start[:self.position - self.last_parse_start]

    def __is_at_end(self):
        return self.position >= len(self.line)
