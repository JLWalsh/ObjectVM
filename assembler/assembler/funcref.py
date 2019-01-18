class FuncRef:

    def __init__(self, func_name: str, class_name: str = None):
        self.class_name = class_name
        self.func_name = func_name

    def __str__(self):
        return f'{self.class_name}::{self.func_name}'
