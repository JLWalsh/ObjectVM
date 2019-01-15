from assembler.lexeme import Lexeme, LexemeType
from assembler.linetokenizer import LineTokenizer


def test_should_parse_one_word():
    line = 'SOME_RANDOM_OPERATION'
    expected = Lexeme(LexemeType.WORD, line, line)

    tokens = LineTokenizer(line).tokenize()

    assert expected == tokens[0]
    assert 1 == len(tokens)


def test_should_parse_int():
    line = '1234567'
    expected = Lexeme(LexemeType.INTEGER, 1234567, line)

    tokens = LineTokenizer(line).tokenize()

    assert expected == tokens[0]
    assert 1 == len(tokens)


def test_should_parse_float():
    line = '996.27'
    expected = Lexeme(LexemeType.FLOAT, 996.27, line)

    tokens = LineTokenizer(line).tokenize()

    assert expected == tokens[0]
    assert 1 == len(tokens)


def test_should_parse_string():
    line = '"Hello, world!"'
    expected = Lexeme(LexemeType.STRING, "Hello, world!", line)

    tokens = LineTokenizer(line).tokenize()

    assert expected == tokens[0]
    assert 1 == len(tokens)


def test_should_parse_escaped_string():
    line = '"Hello, \\" world!"'
    expected = Lexeme(LexemeType.STRING, 'Hello, " world!', line)

    tokens = LineTokenizer(line).tokenize()

    assert expected == tokens[0]
    assert 1 == len(tokens)


def test_should_skip_comment():
    line = '// Hello, world!'

    tokens = LineTokenizer(line).tokenize()

    assert 0 == len(tokens)


def test_should_parse_all_tokens():
    line = 'OP_HELLO 45 274.183 "Hello, \\"world!" // This is a comment'
    word = Lexeme(LexemeType.WORD, 'OP_HELLO', 'OP_HELLO')
    integer = Lexeme(LexemeType.INTEGER, 45, '45')
    float = Lexeme(LexemeType.FLOAT, 274.183, '274.183')
    string = Lexeme(LexemeType.STRING, 'Hello, "world!', '"Hello, \\"world!"')

    tokens = LineTokenizer(line).tokenize()

    assert word == tokens[0]
    assert integer == tokens[1]
    assert float == tokens[2]
    assert string == tokens[3]
    assert 4 == len(tokens)
