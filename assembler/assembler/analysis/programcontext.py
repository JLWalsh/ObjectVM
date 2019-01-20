from typing import List, Optional

from assembler.parsing.instruction import ParsedInstruction
from assembler.parsing.metainstruction import ClassDeclaration, FunctionDeclaration


class Function:

    def __init__(self, name: str, class_name: Optional[str], first_instruction_pos: int):
        self.name = name
        self.class_name = class_name
        self.first_instruction_pos = first_instruction_pos

    def __str__(self):
        return f'[{self.first_instruction_pos}]: {self.name}'

    @staticmethod
    def from_declaration(function_declaration: FunctionDeclaration, first_instruction_pos: int):
        return Function(function_declaration.func_name, function_declaration.class_name, first_instruction_pos)


class FunctionContext:

    def __init__(self, context_name: Optional[str]):
        self.context_name = context_name
        self.functions: List[Function] = []

    def define_function(self, function: Function):
        if self.__has_function(function.name):
            raise ValueError(f"Function {function.name} is already defined for function context {self.context_name}")

        self.functions.append(function)

    def __has_function(self, function_name: str) -> bool:
        for function in self.functions:
            if function.name == function_name:
                return True

        return False

    def __str__(self):
        str = f'{self.context_name}:'

        for function in self.functions:
            str += '\n' + function.name

        return str

    @staticmethod
    def from_class(class_declaration: ClassDeclaration):
        return FunctionContext(class_declaration.class_name)

    @staticmethod
    def global_context():
        return FunctionContext("GLOBAL")


class ProgramContext:

    def __init__(self):
        self.classes: List[FunctionContext] = []
        self.global_function_context: FunctionContext = FunctionContext.global_context()
        self.instruction_pos = -1

    def generate(self, parsed_program: List[ClassDeclaration or FunctionDeclaration or ParsedInstruction]):
        for item in parsed_program:
            if isinstance(item, ClassDeclaration):
                self.__generate_class_context(item)

        for item in parsed_program:
            if isinstance(item, FunctionDeclaration):
                self.__generate_function_context(item)
            elif isinstance(item, ParsedInstruction):
                self.instruction_pos += 1

    def __generate_class_context(self, class_declaration: ClassDeclaration):
        if self.__find_class_named(class_declaration.class_name) is not None:
            raise ValueError(f"Class {class_declaration.class_name} has already been declared")

        class_context = FunctionContext.from_class(class_declaration)
        self.classes.append(class_context)

    def __generate_function_context(self, function_declaration: FunctionDeclaration):
        class_concerned = self.__find_class_named(function_declaration.class_name)
        function = Function.from_declaration(function_declaration, self.instruction_pos)

        if class_concerned is not None:
            class_concerned.define_function(function)
            return

        self.global_function_context.define_function(function)

    def __find_class_named(self, name: str) -> Optional[FunctionContext]:
        for class_context in self.classes:
            if class_context.context_name == name:
                return class_context

        return None
