from typing import List, Optional

from assembler.parsing.instruction import ParsedInstruction
from assembler.parsing.metainstruction import ClassDeclaration, FunctionDeclaration


class Function:

    def __init__(self, name: str, class_name: Optional[str], bytecode_ptr: Optional[int]):
        self.name = name
        self.class_name = class_name
        self.bytecode_ptr = bytecode_ptr

    def __str__(self):
        return f'[{self.bytecode_ptr}]: {self.name}'

    @staticmethod
    def from_declaration(function_declaration: FunctionDeclaration, bytecode_ptr: Optional[int] = None):
        return Function(function_declaration.func_name, function_declaration.class_name, bytecode_ptr)


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
            str += '\n' + function.name + ' @ ' + function.bytecode_ptr.__str__()

        return str

    @staticmethod
    def from_class_declaration(class_declaration: ClassDeclaration):
        return FunctionContext(class_declaration.class_name)

    @staticmethod
    def global_context():
        return FunctionContext(None)


class ProgramContext:

    def __init__(self):
        self.classes: List[FunctionContext] = []
        self.global_function_context: FunctionContext = FunctionContext.global_context()
        self.bytecode_pos = 0

    def generate(self, parsed_program: List[ClassDeclaration or FunctionDeclaration or ParsedInstruction]):
        for item in parsed_program:
            if isinstance(item, ClassDeclaration):
                self.__generate_class_context(item)

        for item in parsed_program:
            if isinstance(item, FunctionDeclaration):
                self.__generate_function_context(item)
            elif isinstance(item, ParsedInstruction):
                self.bytecode_pos += item.size.as_bytes()

    def __generate_class_context(self, class_declaration: ClassDeclaration):
        if self.__find_class_named(class_declaration.class_name) is not None:
            raise ValueError(f"Class {class_declaration.class_name} has already been declared")

        class_context = FunctionContext.from_class_declaration(class_declaration)
        self.classes.append(class_context)

    def __generate_function_context(self, function_declaration: FunctionDeclaration):
        class_concerned = self.__find_class_named(function_declaration.class_name)
        bytecode_pos = None if function_declaration.settings.virtual else self.bytecode_pos
        function = Function.from_declaration(function_declaration, bytecode_pos)

        if class_concerned is not None:
            class_concerned.define_function(function)
            return

        self.global_function_context.define_function(function)

    def __find_class_named(self, name: str) -> Optional[FunctionContext]:
        for class_context in self.classes:
            if class_context.context_name == name:
                return class_context

        return None
