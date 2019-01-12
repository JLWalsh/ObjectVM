from enum import Enum


class Chars(Enum):
    COMMENT = '/'
    STRING = '"'
    WHITESPACE = ' '
    ESCAPE_STRING = '\\'
    DOT = '.'