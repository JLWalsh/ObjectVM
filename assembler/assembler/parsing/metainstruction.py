from typing import List

from assembler.funcsettings import FunctionSettings


class FunctionDeclaration:

    def __init__(self):
        self.func_name = None
        self.settings = FunctionSettings()
        self.class_name = None
        self.override_of: List['FunctionDeclaration'] = []

    def with_name(self, name: str):
        self.func_name = name
        return self

    def with_class_name(self, name: str):
        self.class_name = name
        return self

    def with_settings(self, settings: FunctionSettings):
        self.settings = settings
        return self

    def will_override(self, override_of: 'FunctionDeclaration'):
        self.override_of.append(override_of)
        return self

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
