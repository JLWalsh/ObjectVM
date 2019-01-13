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

    def __init__(self, token_type: LexemeType, parsed_value, raw: str):
        self.token_type = token_type
        self.raw = raw
        self.parsed_value = parsed_value
