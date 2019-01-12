from typing import List

NEW_LINE = '\n'
COMMAND_PREFIX = '#'


class Parser:

    def __init__(self, instruction_parser):
        self.instruction_parser = instruction_parser

    def parse(self, source: str):
        lines = source.split(NEW_LINE)

        return lines

    def __parse_lines(self, lines: List[str]):
        parsed_lines = []

        for line in lines:
            is_command = self.__line_is_command(line)

            if not is_command:
                parsed_instruction = self.instruction_parser.parse_line(line)
                parsed_lines.append(parsed_instruction)

        return parsed_lines

    def __line_is_command(self, line):
        return line.replace(" ", "").startsWith(COMMAND_PREFIX)
