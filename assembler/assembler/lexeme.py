from enum import Enum


class LexemeType(Enum):
    WORD = 0
    INTEGER = 1
    FLOAT = 2
    STRING = 3
    META = 4  # when a line starts with #
    BODY_DECLARATION = 5  # when a line ends with ::
    IMPLEMENTATION = 6  # the ->
    LEFT_PAREN = 7
    RIGHT_PAREN = 8


class Lexeme:

    def __init__(self, lexeme_type: LexemeType, parsed_value, raw: str):
        self.lexeme_type = lexeme_type
        self.raw = raw
        self.parsed_value = parsed_value

    def __str__(self):
        return f"[{self.lexeme_type}]: {self.parsed_value}"

    def __eq__(self, other):
        if isinstance(other, Lexeme):
            return other.lexeme_type == self.lexeme_type \
                   and other.raw == self.raw \
                   and other.parsed_value == self.parsed_value
        return False
