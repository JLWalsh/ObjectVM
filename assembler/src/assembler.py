import sys

from parser import Parser


def main():
    if len(sys.argv) < 2:
        print("No source file provided.")
        exit(1)

    file_name = sys.argv[1]
    source = read_source(file_name)

    parser = Parser(source)
    tokens = parser.parse()
    print(tokens)

    errors = parser.get_errors()
    for error in errors:
        print(error)


def read_source(file_name):
    file = open(file_name, "r")
    source = file.read()
    file.close()

    return source


if __name__ == "__main__":
    main()
