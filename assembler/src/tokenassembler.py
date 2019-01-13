from lexeme import Lexeme, LexemeType


class TokenAssembler:

    @staticmethod
    def assemble_integer(literal: str) -> Lexeme:
        integer = int(literal)

        return Lexeme(LexemeType.INTEGER, integer, literal)

    @staticmethod
    def assemble_float(literal: str) -> Lexeme:
        float_value = float(literal)

        return Lexeme(LexemeType.FLOAT, float_value, literal)
