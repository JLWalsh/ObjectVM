from enum import Enum


class Chars(Enum):
    COMMENT = '/'
    STRING = '"'
    WHITESPACE = ' '
    ESCAPE_STRING = '\\'
    DOT = '.'
    NEWLINE = '\n'
    META_PREFIX = '#'
    LEFT_PAREN = '('
    RIGHT_PAREN = ')'
    COLON = ':'
    NEGATE = '-'
