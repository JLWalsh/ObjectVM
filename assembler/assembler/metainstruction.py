from typing import List


class FunctionDeclarationSettings:

    def __init__(self, static: bool = False, abstract: bool = False, virtual: bool = False, num_args: int = 0):
        self.static = static
        self.abstract = abstract
        self.virtual = virtual
        self.num_args = num_args

    def with_num_args(self, num_args: int):
        self.num_args = num_args

    def make_abstract(self):
        self.abstract = True

    def make_virtual(self):
        self.virtual = True

    def make_static(self):
        self.static = True


class FunctionDeclaration:

    def __init__(self):
        self.func_name = None
        self.settings = None
        self.class_name = None

    def with_name(self, name: str):
        self.func_name = name

    def with_class_name(self, name: str):
        self.class_name = name

    def with_settings(self, settings: FunctionDeclarationSettings):
        self.settings = settings

    def __str__(self):
        str_val = f'{self.class_name}::{self.func_name}'

        if not self.settings:
            return str_val

        return str_val + f" {str(self.settings)}"


class ClassDeclaration:

    def __init__(self):
        self.class_name = None
        self.implementations = None

    def with_name(self, name: str):
        self.class_name = name
        self.implementations = []

    def with_implementations(self, implementations: List[str]):
        self.implementations = implementations

    def __str__(self):
        str_val = f'class {self.class_name}'

        if len(self.implementations) > 0:
            str_val += ' implements'

        for implementation in self.implementations:
            str_val += f' {implementation}'

        return str_val
