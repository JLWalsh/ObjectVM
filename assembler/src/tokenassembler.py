from token import Token, TokenType


class TokenAssembler:

    @staticmethod
    def assemble_integer(literal: str) -> Token:
        integer = int(literal)

        return Token(TokenType.INTEGER, integer, literal)

    @staticmethod
    def assemble_float(literal: str) -> Token:
        float_value = float(literal)

        return Token(TokenType.FLOAT, float_value, literal)
