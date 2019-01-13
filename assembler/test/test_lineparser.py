from linetokenizer import LineTokenizer
from lexeme import Lexeme, LexemeType


def test_should_parse_one_word():
    line = 'SOME_RANDOM_OPERATION'
    expected = Lexeme(LexemeType.WORD, line, line)

    tokens = LineTokenizer(line).tokenize()

    assert expected == tokens[0]
    assert 1 == len(tokens)

# def test_should_parse_int(self):
#
# def test_should_parse_float(self):
#
# def test_should_parse_string(self):
#
# def test_should_parse_escaped_string(self):
#
# def test_should_skip_comment(self):
#
# def test_should_parse_all_tokens(self):
