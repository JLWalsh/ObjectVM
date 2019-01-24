CHAR_BIT = 8


class Size:

    def __init__(self, num_bits: int):
        self.num_bits = num_bits

    def as_bytes(self):
        return self.num_bits / CHAR_BIT

    def __add__(self, other: 'Size'):
        return Size(self.num_bits + other.num_bits)

    @staticmethod
    def from_bytes(bytes: int) -> 'Size':
        return Size(bytes * CHAR_BIT)
