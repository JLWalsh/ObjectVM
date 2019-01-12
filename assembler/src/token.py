from enum import Enum


class TokenType(Enum):
    WORD = 0
    INTEGER = 1
    FLOAT = 2
    STRING = 3


class Token:

    def __init__(self, token_type: TokenType, parsed_value, raw: str):
        self.token_type = token_type
        self.raw = raw
        self.parsed_value = parsed_value

