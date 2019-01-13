from enum import Enum
from typing import Dict, List


class FunctionDeclarationSetting(Enum):
    NUM_ARGS = 0
    ABSTRACT = 1
    STATIC = 2


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


class ClassDeclaration:

    def __init__(self):
        self.class_name = None
        self.implementations = None

    def with_name(self, name: str):
        self.class_name = name

    def with_implementations(self, implementations: List[str]):
        self.implementations = implementations


class InterfaceDeclaration:

    def __init__(self, name: str):
        self.name = name
