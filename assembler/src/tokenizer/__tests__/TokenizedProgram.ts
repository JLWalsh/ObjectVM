import { Coordinate } from "../../Coordinate";
import { ParseError } from "../ParseError";
import { TokenizedLine } from "../TokenizedLine";
import { TokenizedProgram } from "../TokenizedProgram";

describe("TokenizedProgram", () => {

  const ERROR = new ParseError("", Coordinate.zero());

  let program: TokenizedProgram;

  describe("a program with errors", () => {

    beforeAll(() => {
      const lineWithErrors = new TokenizedLine("", [], 0, [ERROR]);
      program = new TokenizedProgram([lineWithErrors]);
    });

    it("should have errors", () => {
      const hasErrors = program.hasErrors();

      expect(hasErrors).toBeTruthy();
    });
  });

  describe("a program no errors", () => {

    beforeAll(() => {
      const line = new TokenizedLine("", [], 0, []);
      program = new TokenizedProgram([line]);
    });

    it("should have errors", () => {
      const hasErrors = program.hasErrors();

      expect(hasErrors).toBeFalsy();
    });
  });
});
