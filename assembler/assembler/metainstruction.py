from enum import Enum
from typing import Dict, List


class FunctionDeclarationSetting(Enum):
    NUM_ARGS = 0
    ABSTRACT = 1
    STATIC = 2
    VIRTUAL = 3


class FunctionDeclaration:

    def __init__(self):
        self.func_name = None
        self.settings = None
        self.class_name = None

    def with_name(self, name: str):
        self.func_name = name

    def with_class_name(self, name: str):
        self.class_name = name

    def with_settings(self, settings: Dict[FunctionDeclarationSetting, any]):
        self.settings = settings

    def __str__(self):
        str_val = f'{self.class_name}::{self.func_name}'

        if not self.settings:
            return str_val

        for setting in enumerate(self.settings):
            str_val += str(setting)

        return str_val

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
