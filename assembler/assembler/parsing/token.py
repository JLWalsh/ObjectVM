from enum import Enum


class TokenType(Enum):
    WORD = 0
    INT = 1
    FLOAT = 2
    STRING = 3
    META_START = 4
    QUOTE_BLOCK = 5
    LEFT_PAREN = 6
    RIGHT_PAREN = 7
    IMPLEMENTATION = 8


class Token:

    def __init__(self, token_type: TokenType, parsed_value, raw: str):
        self.token_type = token_type
        self.raw = raw
        self.parsed_value = parsed_value

    def is_type(self, lexeme_type: TokenType):
        return self.token_type == lexeme_type

    def __str__(self):
        return f"[{self.token_type}]: {self.parsed_value}"

    def __eq__(self, other):
        if isinstance(other, Token):
            return other.is_type(self.token_type) \
                   and other.raw == self.raw \
                   and other.parsed_value == self.parsed_value
        return False
