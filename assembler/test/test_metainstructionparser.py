import pytest

from assembler.parsing.metainstruction import ClassDeclaration
from assembler.parsing.metainstructionparser import MetaInstructionParser
from assembler.parsing.token import Token, TokenType
from test.expect import expect

META_START = Token(TokenType.META_START, "#", "#")
QUOTE_BLOCK = Token(TokenType.QUOTE_BLOCK, "::", "::")
LEFT_PAREN = Token(TokenType.LEFT_PAREN, "(", "(")
RIGHT_PAREN = Token(TokenType.RIGHT_PAREN, ")", ")")
CLASS = Token(TokenType.WORD, "class", "class")
IMPLEMENTATION = Token(TokenType.IMPLEMENTATION, "->", "->")


def test_given_no_meta_lexeme_at_start_should_throw():
    lexemes = []

    with pytest.raises(Exception) as error:
        MetaInstructionParser(lexemes).parse()

    expected_error = ValueError("Instruction should begin with #")
    assert expect(error).is_error(expected_error)


def test_should_parse_class_declaration():
    class_name = Token(TokenType.WORD, "Engine", "Engine")
    lexemes = [META_START, CLASS, class_name]

    class_declaration = MetaInstructionParser(lexemes).parse()

    assert isinstance(class_declaration, ClassDeclaration)
    assert class_declaration.class_name == "Engine"


def test_should_parse_class_declaration_with_implementations():
    class_name = Token(TokenType.WORD, "Engine", "Engine")
    first_implementation = Token(TokenType.WORD, "Interface1", "Interface1")
    second_implementation = Token(TokenType.WORD, "Interface2", "Interface2")
    lexemes = [META_START, CLASS, class_name, QUOTE_BLOCK, LEFT_PAREN, first_implementation, second_implementation,
               RIGHT_PAREN]

    class_declaration = MetaInstructionParser(lexemes).parse()

    assert isinstance(class_declaration, ClassDeclaration)
    assert class_declaration.class_name == "Engine"
    assert class_declaration.implementations[0] == "Interface1"
    assert class_declaration.implementations[1] == "Interface2"


def test_given_excess_lexemes_for_class_declaration_should_throw():
    class_name = Token(TokenType.WORD, "Engine", "Engine")
    lexemes = [META_START, CLASS, class_name, QUOTE_BLOCK, LEFT_PAREN, RIGHT_PAREN, class_name]

    with pytest.raises(Exception) as error:
        MetaInstructionParser(lexemes).parse()

    expected_error = ValueError("Too many arguments provided for class declaration")
    assert expect(error).is_error(expected_error)


def test_should_parse_classless_func_declaration():
    func_name = Token(TokenType.WORD, "ClasslessFunc", "ClasslessFunc")
    lexemes = [META_START, func_name]

    func_declaration = MetaInstructionParser(lexemes).parse()

    assert func_declaration.func_name == "ClasslessFunc"
    assert func_declaration.class_name is None


def test_should_parse_classless_func_declaration_settings():
    func_name = Token(TokenType.WORD, "ClasslessFunc", "ClasslessFunc")
    num_args = Token(TokenType.INT, 2, "2")
    lexemes = [META_START, func_name, QUOTE_BLOCK, LEFT_PAREN, num_args, RIGHT_PAREN]

    func_declaration_settings = MetaInstructionParser(lexemes).parse().settings

    assert func_declaration_settings.num_args == 2


def test_should_parse_class_func_declaration():
    class_name = Token(TokenType.WORD, "ClassName", "ClassName")
    func_name = Token(TokenType.WORD, "FuncName", "FuncName")
    lexemes = [META_START, class_name, QUOTE_BLOCK, func_name]

    func_declaration = MetaInstructionParser(lexemes).parse()

    assert func_declaration.func_name == "FuncName"
    assert func_declaration.class_name == "ClassName"


def test_should_parse_all_func_settings():
    func_name = Token(TokenType.WORD, "ClasslessFunc", "ClasslessFunc")
    num_args = Token(TokenType.INT, 2, "2")
    static = Token(TokenType.WORD, "static", "static")
    virtual = Token(TokenType.WORD, "virtual", "virtual")
    lexemes = [META_START, func_name, QUOTE_BLOCK, LEFT_PAREN, num_args, static, virtual, RIGHT_PAREN]

    func_declaration_settings = MetaInstructionParser(lexemes).parse().settings

    assert func_declaration_settings.num_args == 2
    assert func_declaration_settings.virtual
    assert func_declaration_settings.static


def test_given_func_settings_missing_closing_paren_should_throw():
    func_name = Token(TokenType.WORD, "ClasslessFunc", "ClasslessFunc")
    lexemes = [META_START, func_name, QUOTE_BLOCK, LEFT_PAREN]

    with pytest.raises(Exception) as error:
        MetaInstructionParser(lexemes).parse()

    expected_error = ValueError("Function settings have not been terminated with char )")
    assert expect(error).is_error(expected_error)


def test_should_parse_overriding_function():
    class_name = Token(TokenType.WORD, "ClassName", "ClassName")
    func_name = Token(TokenType.WORD, "FuncName", "FuncName")
    overriden_class_name = Token(TokenType.WORD, "Overriden", "Overriden")
    overriden_function_name = Token(TokenType.WORD, "Function", "Function")
    lexemes = [META_START, class_name, QUOTE_BLOCK, func_name, IMPLEMENTATION, overriden_class_name, QUOTE_BLOCK,
               overriden_function_name]

    func_declaration = MetaInstructionParser(lexemes).parse()

    assert func_declaration.func_name == "FuncName"
    assert func_declaration.class_name == "ClassName"
    assert func_declaration.function_overrides.func_name == "Function"
    assert func_declaration.function_overrides.class_name == "Overriden"


def test_given_overriding_function_with_settings_should_throw():
    class_name = Token(TokenType.WORD, "ClassName", "ClassName")
    func_name = Token(TokenType.WORD, "FuncName", "FuncName")
    overriden_class_name = Token(TokenType.WORD, "Overriden", "Overriden")
    overriden_function_name = Token(TokenType.WORD, "Function", "Function")
    lexemes = [META_START, class_name, QUOTE_BLOCK, func_name, QUOTE_BLOCK, LEFT_PAREN, RIGHT_PAREN, IMPLEMENTATION,
               overriden_class_name, QUOTE_BLOCK,
               overriden_function_name]

    with pytest.raises(Exception) as error:
        MetaInstructionParser(lexemes).parse()

    expected_error = ValueError("Function that overrides another may not have settings as they will be inherited")
    assert expect(error).is_error(expected_error)
