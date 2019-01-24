import sys

from assembler.analysis.bytecoderesolver import BytecodeResolver
from assembler.parsing.parser import Parser


def main():
    if len(sys.argv) < 2:
        print("No source file provided.")
        exit(1)

    file_name = sys.argv[1]
    source = read_source(file_name)

    parser = Parser(source)
    program = parser.parse()

    if len(parser.get_errors()) == 0:
        context = BytecodeResolver()
        context.resolve(program)

        for c in context.classes:
            print("class" + str(c))

        print("GLOBAL CONTEXT:")
        print(context.global_function_context)
    else:
        print("Got errorz")
        for error in parser.get_errors():
            print(error)


def read_source(file_name):
    file = open(file_name, "r")
    source = file.read()
    file.close()

    return source


if __name__ == "__main__":
    main()
