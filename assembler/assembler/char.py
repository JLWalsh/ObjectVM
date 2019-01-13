class Char:

    @staticmethod
    def is_alpha(char: chr):
        return ('a' <= char <= 'z') or ('A' <= char <= 'Z') or char == '_'

    @staticmethod
    def is_numeric(char: chr):
        return '0' <= char <= '9'
