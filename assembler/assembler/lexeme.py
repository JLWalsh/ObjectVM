from enum import Enum


class LexemeType(Enum):
    WORD = 0
    INT = 1
    FLOAT = 2
    STRING = 3
    META_START = 4
    QUOTE_BLOCK = 5
    LEFT_PAREN = 6
    RIGHT_PAREN = 7


class Lexeme:

    def __init__(self, lexeme_type: LexemeType, parsed_value, raw: str):
        self.lexeme_type = lexeme_type
        self.raw = raw
        self.parsed_value = parsed_value

    def is_type(self, lexeme_type: LexemeType):
        return self.lexeme_type == lexeme_type

    def __str__(self):
        return f"[{self.lexeme_type}]: {self.parsed_value}"

    def __eq__(self, other):
        if isinstance(other, Lexeme):
            return other.is_type(self.lexeme_type) \
                   and other.raw == self.raw \
                   and other.parsed_value == self.parsed_value
        return False
