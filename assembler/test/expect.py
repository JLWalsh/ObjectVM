class Expectation:

    def __init__(self, subject: any):
        self.subject = subject

    def is_error(self, expected_error: Exception) -> bool:
        is_same_instance_type = isinstance(self.subject.value, type(expected_error))
        is_same_message = str(self.subject.value) == str(expected_error)

        return is_same_instance_type and is_same_message


def expect(subject: any):
    return Expectation(subject)
