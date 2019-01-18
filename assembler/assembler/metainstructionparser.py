from typing import List, Dict, Optional

from assembler.lexeme import Lexeme, LexemeType
from assembler.metainstruction import FunctionDeclaration, FunctionDeclarationSetting, ClassDeclaration
from assembler.metakeyword import MetaKeyword


class KeywordParser:

    def __init__(self, keywords: Dict[str, MetaKeyword]):
        self.keywords = keywords

    def parse(self, lexeme: Lexeme) -> MetaKeyword:
        if lexeme.parsed_value not in self.keywords:
            if lexeme.lexeme_type == LexemeType.WORD:
                return MetaKeyword.WORD
            else:
                return MetaKeyword.UNKNOWN

        return self.keywords[lexeme.parsed_value]

    @staticmethod
    def default():
        keywords = {
            'static': MetaKeyword.STATIC,
            'abstract': MetaKeyword.ABSTRACT,
            'class': MetaKeyword.CLASS,
            'virtual': MetaKeyword.VIRTUAL
        }

        return KeywordParser(keywords)


class MetaInstructionParser:

    def __init__(self, lexemes: List[Lexeme], keyword_parser=KeywordParser.default()):
        self.lexemes = lexemes
        self.keyword_parser = keyword_parser
        self.position = 0

    def parse(self):
        if not self.__match_lexeme(LexemeType.META):
            raise ValueError("Instruction should begin with #")

        if self.__match_keyword(MetaKeyword.CLASS):
            return self.__parse_class_declaration()
        elif self.__match_keyword(MetaKeyword.WORD):
            return self.__parse_func_declaration()
        else:
            raise ValueError("Instruction should either be a class declaration or a function declaration")

    def __parse_func_declaration(self) -> FunctionDeclaration:
        self.__match_lexeme(LexemeType.BODY_DECLARATION)

        if self.__match_keyword(MetaKeyword.WORD):
            return self.__parse_class_func_declaration()
        else:
            return self.__parse_classless_func_declaration()

    def __parse_classless_func_declaration(self) -> FunctionDeclaration:
        func_declaration = FunctionDeclaration()
        func_declaration.with_name(self.lexemes[1].parsed_value)  # If is static classless (Method::)

        if self.__match_lexeme(LexemeType.LEFT_PAREN):
            settings = self.__parse_func_settings()
            func_declaration.with_settings(settings)

        if not self.__is_at_end():
            raise ValueError("Classless function declaration has excess parameters")

        return func_declaration

    def __parse_class_func_declaration(self) -> FunctionDeclaration:
        func_declaration = FunctionDeclaration()
        func_declaration.with_name(self.lexemes[3].parsed_value)  # If is class func (Class::Method::)
        func_declaration.with_class_name(self.lexemes[1].parsed_value)

        if self.__match_lexeme(LexemeType.BODY_DECLARATION):
            if not self.__match_lexeme(LexemeType.LEFT_PAREN):
                raise ValueError("Function declaration should be followed by settings")

            settings = self.__parse_func_settings()
            func_declaration.with_settings(settings)

        if not self.__is_at_end():
            raise ValueError("Function declaration has excess parameters")

        return func_declaration

    def __parse_func_settings(self) -> Dict[FunctionDeclarationSetting, any]:
        settings = {}

        num_args_lexeme = self.__match_lexeme(LexemeType.INTEGER)
        if num_args_lexeme:
            settings[FunctionDeclarationSetting.NUM_ARGS] = num_args_lexeme.parsed_value

        # TODO in the future, implement parsing that doesn't require any specific order for the arguments
        if self.__match_keyword(MetaKeyword.ABSTRACT):
            settings[FunctionDeclarationSetting.ABSTRACT] = True

        if self.__match_keyword(MetaKeyword.STATIC):
            settings[FunctionDeclarationSetting.STATIC] = True

        if self.__match_keyword(MetaKeyword.VIRTUAL):
            settings[FunctionDeclarationSetting.VIRTUAL] = True

        if not self.__match_lexeme(LexemeType.RIGHT_PAREN):
            raise ValueError("Function settings have not been terminated with char )")

        return settings

    def __parse_class_declaration(self) -> ClassDeclaration:
        class_declaration = ClassDeclaration()

        if not self.__match_keyword(MetaKeyword.WORD):
            raise ValueError("Class declaration should be followed by class name")

        class_declaration.with_name(self.lexemes[2].parsed_value)

        if self.__match_lexeme(LexemeType.BODY_DECLARATION):
            if not self.__match_lexeme(LexemeType.LEFT_PAREN):
                raise ValueError("Class declaration should be followed by implementations")

            implementations = self.__parse_class_implementations()
            class_declaration.with_implementations(implementations)

        return class_declaration

    def __parse_class_implementations(self) -> List[str]:
        implementations = []
        while not self.__is_at_end() and self.__peek().lexeme_type != LexemeType.RIGHT_PAREN:
            class_name = self.__match_keyword(MetaKeyword.WORD)

            if not class_name:
                raise ValueError(f"Class implementations should only be words (got {self.__peek().parsed_value})")

            implementations.append(class_name.parsed_value)

        if not self.__match_lexeme(LexemeType.RIGHT_PAREN):
            raise ValueError(f"Class implementations must be followed by )")

        return implementations

    def __match_keyword(self, wanted_keyword: MetaKeyword):
        next = self.__peek()
        if next is None:
            return False

        keyword = self.keyword_parser.parse(next)

        if keyword == wanted_keyword:
            return self.__advance()

        return False

    def __match_lexeme(self, wanted_lexeme: LexemeType):
        lexeme = self.__peek()
        if lexeme is None:
            return False

        if lexeme is not None and lexeme.lexeme_type == wanted_lexeme:
            return self.__advance()

        return False

    def __peek(self) -> Optional[Lexeme]:
        if self.__is_at_end():
            return None

        return self.lexemes[self.position]

    def __advance(self):
        lexeme = self.__peek()

        self.position += 1

        return lexeme

    def __is_at_end(self):
        return self.position >= len(self.lexemes)
