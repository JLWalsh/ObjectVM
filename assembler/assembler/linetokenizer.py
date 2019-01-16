from assembler.char import Char
from assembler.chars import Chars
from assembler.lexeme import Lexeme, LexemeType
from assembler.tokenassembler import TokenAssembler


class LineTokenizer:

    def __init__(self, line: str):
        self.line = line
        self.position = 0
        self.last_parse_start = 0
        self.tokens = []

    def tokenize(self):
        while not self.__is_at_end():
            self.last_parse_start = self.position

            char = self.__advance()

            if Char.is_numeric(char):
                self.__parse_numeric()
            elif Char.is_alpha(char):
                self.__parse_word()
            elif char == Chars.NEGATE.value:
                self.__parse_numeric()
            elif char == Chars.STRING.value:
                self.__parse_string()
            elif char == Chars.META_PREFIX.value:
                self.__push_single_char(char, LexemeType.META)
            elif char == Chars.LEFT_PAREN.value:
                self.__push_single_char(char, LexemeType.LEFT_PAREN)
            elif char == Chars.RIGHT_PAREN.value:
                self.__push_single_char(char, LexemeType.RIGHT_PAREN)
            elif char == Chars.COLON.value:
                self.__parse_body_declaration()
            elif char == Chars.WHITESPACE.value:
                continue
            elif char == Chars.COMMENT.value and self.__peek() == Chars.COMMENT.value:
                break
            else:
                raise ValueError(f"Unrecognized character: {char}")

        return self.tokens

    def __push_single_char(self, char: chr, token_type: LexemeType):
        token = Lexeme(token_type, char, char)
        self.tokens.append(token)

    def __parse_body_declaration(self):
        if self.__peek() != Chars.COLON.value:
            raise ValueError("Incomplete body declaration. Missing char : after")

        self.__advance()  # Consume the second colon

        literal = self.__extract_literal()
        token = Lexeme(LexemeType.BODY_DECLARATION, literal, literal)
        self.tokens.append(token)

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
        token = Lexeme(LexemeType.WORD, literal, literal)

        self.tokens.append(token)

    def __parse_string(self):
        string = ''

        while not self.__is_at_end() and self.__peek() != Chars.STRING.value:
            string += self.__advance()

            if self.__peek() == Chars.ESCAPE_STRING.value:
                self.__advance()  # Skip escape character
                string += self.__advance()  # Skip over escaped value

        if self.__peek() != Chars.STRING.value:
            raise ValueError("Unterminated string")

        self.__advance()  # Consume the quote at end of string

        literal = self.__extract_literal()
        token = Lexeme(LexemeType.STRING, string, literal)

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
