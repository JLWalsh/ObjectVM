class Int:

    def __init__(self, byte_size: int, char_bit: int):
        self.byte_size = byte_size
        self.char_bit = char_bit

    def can_hold(self, value: int) -> bool:
        max_unsigned_val = pow(2, self.byte_size * self.char_bit)

        max_positive_val = max_unsigned_val / 2 - 1
        max_negative_val = max_unsigned_val / 2

        return max_negative_val <= value <= max_positive_val

    @staticmethod
    def default():
        return Int(2, 8)


class UInt:

    def __init__(self, byte_size: int, char_bit: int):
        self.byte_size = byte_size
        self.char_bit = char_bit

    def can_hold(self, value: int) -> bool:
        if value < 0:
            return False

        max_val = pow(2, self.byte_size * self.char_bit) - 1

        return value <= max_val

    @staticmethod
    def default():
        return UInt(2, 8)
