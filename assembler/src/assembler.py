from parser import Parser
import sys


def main():
    if len(sys.argv) < 2:
        print("No source file provided.")
        exit(1)

    file_name = sys.argv[1]
    source = read_source(file_name)

    tokenizer = Parser()
    tokens = tokenizer.parse(source)
    print(tokens)


def read_source(file_name):
    file = open(file_name, "r")
    source = file.read()
    file.close()

    return source


if __name__ == "__main__":
    main()
