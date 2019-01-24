class FunctionSettings:

    def __init__(self, static: bool = False, virtual: bool = False, num_args: int = 0):
        self.static = static
        self.virtual = virtual
        self.num_args = num_args

    def with_num_args(self, num_args: int):
        self.num_args = num_args

    def make_virtual(self):
        self.virtual = True

    def make_static(self):
        self.static = True

    def __str__(self):
        str = f'Num args: {self.num_args}'

        if self.static:
            str += ', static'

        if self.virtual:
            str += ', virtual'

        return str
