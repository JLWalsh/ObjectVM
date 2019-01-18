import string

from assembler.char import Char


def test_given_lowercase_alphabet_all_should_be_alpha():
    alphabet = list(string.ascii_lowercase)

    for letter in alphabet:
        is_alpha = Char.is_alpha(letter)

        assert is_alpha


def test_given_uppercase_alphabet_all_should_be_alpha():
    alphabet = list(string.ascii_uppercase)

    for letter in alphabet:
        is_alpha = Char.is_alpha(letter)

        assert is_alpha


def test_given_special_char_should_not_be_alpha():
    non_alpha = '#'

    is_alpha = Char.is_alpha(non_alpha) == False

    assert is_alpha


def test_given_number_should_not_be_alpha():
    number = '0'

    is_alpha = Char.is_alpha(number) == False

    assert is_alpha


def test_given_underscore_should_be_alpha():
    underscore = '_'

    assert Char.is_alpha(underscore) == True


def test_given_all_numbers_should_be_numeric():
    numbers = list(string.digits)

    for digit in numbers:
        is_numeric_digit_true = Char.is_numeric(digit) == True

        assert is_numeric_digit_true


def test_given_letter_should_not_be_numeric():
    letter = 'a'

    is_numeric = Char.is_numeric(letter) == False

    assert is_numeric
