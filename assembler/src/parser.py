from typing import List

from chars import Chars


class Parser:

    def __init__(self, source: str):
        self.source = source
        self.errors = []

    def parse(self):
        lines = self.source.split(Chars.NEWLINE.value)

        return self.__parse_lines(lines)

    def errors(self):
        return self.errors

    def __parse_lines(self, lines: List[str]):
        parsed_lines = []

        for line in lines:


            if not is_command:
                parsed_instruction = self.instruction_parser.parse_line(line)
                parsed_lines.append(parsed_instruction)

        return parsed_lines

