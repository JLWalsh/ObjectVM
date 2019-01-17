class Int:

    def __init__(self, byte_size: int):
        self.byte_size = byte_size

    def can_hold(self, value: int) -> bool:
        max_unsigned_val = pow(2, self.byte_size * 8)

        max_positive_val = max_unsigned_val / 2 - 1
        max_negative_val = max_unsigned_val / 2

        return max_negative_val <= value <= max_positive_val

    @staticmethod
    def default_size():
        return Int(2)


class UInt:

    def __init__(self, byte_size: int):
        self.byte_size = byte_size

    def can_hold(self, value: int) -> bool:
        if value < 0:
            return False

        max_val = pow(2, self.byte_size * 8) - 1

        return value <= max_val

    @staticmethod
    def default_size():
        return UInt(2)
