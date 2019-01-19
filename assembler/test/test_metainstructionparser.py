import pytest

from assembler.lexeme import Lexeme, LexemeType
from assembler.metainstruction import ClassDeclaration
from assembler.metainstructionparser import MetaInstructionParser
from test.expect import expect

META_START = Lexeme(LexemeType.META_START, "#", "#")
QUOTE_BLOCK = Lexeme(LexemeType.QUOTE_BLOCK, "::", "::")
LEFT_PAREN = Lexeme(LexemeType.LEFT_PAREN, "(", "(")
RIGHT_PAREN = Lexeme(LexemeType.RIGHT_PAREN, ")", ")")
CLASS = Lexeme(LexemeType.WORD, "class", "class")


def test_given_no_meta_lexeme_at_start_should_throw():
    lexemes = []

    with pytest.raises(Exception) as error:
        MetaInstructionParser(lexemes).parse()

    expected_error = ValueError("Instruction should begin with #")
    assert expect(error).is_error(expected_error)


def test_should_parse_class_declaration():
    class_name = Lexeme(LexemeType.WORD, "Engine", "Engine")
    lexemes = [META_START, CLASS, class_name]

    class_declaration = MetaInstructionParser(lexemes).parse()

    assert isinstance(class_declaration, ClassDeclaration)
    assert class_declaration.class_name == "Engine"


def test_should_parse_class_declaration_with_implementations():
    class_name = Lexeme(LexemeType.WORD, "Engine", "Engine")
    first_implementation = Lexeme(LexemeType.WORD, "Interface1", "Interface1")
    second_implementation = Lexeme(LexemeType.WORD, "Interface2", "Interface2")
    lexemes = [META_START, CLASS, class_name, QUOTE_BLOCK, LEFT_PAREN, first_implementation, second_implementation,
               RIGHT_PAREN]

    class_declaration = MetaInstructionParser(lexemes).parse()

    assert isinstance(class_declaration, ClassDeclaration)
    assert class_declaration.class_name == "Engine"
    assert class_declaration.implementations[0] == "Interface1"
    assert class_declaration.implementations[1] == "Interface2"


def test_given_excess_lexemes_for_class_declaration_should_throw():
    class_name = Lexeme(LexemeType.WORD, "Engine", "Engine")
    lexemes = [META_START, CLASS, class_name, QUOTE_BLOCK, LEFT_PAREN, RIGHT_PAREN, class_name]

    with pytest.raises(Exception) as error:
        MetaInstructionParser(lexemes).parse()

    expected_error = ValueError("Too many arguments provided for class declaration")
    assert expect(error).is_error(expected_error)


def test_should_parse_classless_func_declaration():
    func_name = Lexeme(LexemeType.WORD, "ClasslessFunc", "ClasslessFunc")
    lexemes = [META_START, func_name]

    func_declaration = MetaInstructionParser(lexemes).parse()

    assert func_declaration.func_name == "ClasslessFunc"
    assert func_declaration.class_name is None


def test_should_parse_classless_func_declaration_settings():
    func_name = Lexeme(LexemeType.WORD, "ClasslessFunc", "ClasslessFunc")
    num_args = Lexeme(LexemeType.INT, 2, "2")
    lexemes = [META_START, func_name, QUOTE_BLOCK, LEFT_PAREN, num_args, RIGHT_PAREN]

    func_declaration_settings = MetaInstructionParser(lexemes).parse().settings

    assert func_declaration_settings.num_args == 2


def test_should_parse_class_func_declaration():
    class_name = Lexeme(LexemeType.WORD, "ClassName", "ClassName")
    func_name = Lexeme(LexemeType.WORD, "FuncName", "FuncName")
    lexemes = [META_START, class_name, QUOTE_BLOCK, func_name]

    func_declaration = MetaInstructionParser(lexemes).parse()

    assert func_declaration.func_name == "FuncName"
    assert func_declaration.class_name == "ClassName"


def test_should_parse_all_func_settings():
    func_name = Lexeme(LexemeType.WORD, "ClasslessFunc", "ClasslessFunc")
    num_args = Lexeme(LexemeType.INT, 2, "2")
    static = Lexeme(LexemeType.WORD, "static", "static")
    virtual = Lexeme(LexemeType.WORD, "virtual", "virtual")
    lexemes = [META_START, func_name, QUOTE_BLOCK, LEFT_PAREN, num_args, static, virtual, RIGHT_PAREN]

    func_declaration_settings = MetaInstructionParser(lexemes).parse().settings

    assert func_declaration_settings.num_args == 2
    assert func_declaration_settings.virtual
    assert func_declaration_settings.static


def test_given_func_settings_missing_closing_paren_should_throw():
    func_name = Lexeme(LexemeType.WORD, "ClasslessFunc", "ClasslessFunc")
    lexemes = [META_START, func_name, QUOTE_BLOCK, LEFT_PAREN]

    with pytest.raises(Exception) as error:
        MetaInstructionParser(lexemes).parse()

    expected_error = ValueError("Function settings have not been terminated with char )")
    assert expect(error).is_error(expected_error)
