from typing import List

from lexeme import Lexeme


class InstructionParser:

    def __init__(self, lexemes: List[Lexeme]):
        self.lexemes = lexemes

    def parse(self):
        return "NOT NYET!"
