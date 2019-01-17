class Float:

    def __init__(self, byte_size: int):
        self.byte_size = byte_size

    def can_hold(self, value: float) -> bool:
        # TODO figure out formula to determine a float's max size
        # according to the size of its exponent and mantissa bits
        return True

    @staticmethod
    def default_size():
        return Float(4)
