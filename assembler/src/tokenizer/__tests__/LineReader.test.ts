import { Char, LineReader } from "../LineReader";

describe("LineReader", () => {

  let lineReader: LineReader;

  describe("given a line reader at start of line", () => {
    const LINE = "hello";
    const INITIAL_POSITION = 0;

    beforeEach(() => {
      lineReader = LineReader.from(LINE);
    });

    describe("when advancing", () => {
      it("should advance by one", () => {
        lineReader.advance();

        const expectedPosition = INITIAL_POSITION + 1;
        expect(lineReader.getPosition()).toEqual(expectedPosition);
      });
    });

    describe("when matching function succesfully", () => {
      const SUCCESS_MATCH_FUNC = (c: Char) => c === "h";

      it("should match", () => {
        const matches = lineReader.matchFunc(SUCCESS_MATCH_FUNC);

        expect(matches).toBeTruthy();
      });

      it("should advance by one", () => {
        lineReader.matchFunc(SUCCESS_MATCH_FUNC);

        const position = lineReader.getPosition();
        expect(position).toEqual(INITIAL_POSITION + 1);
      });
    });

    describe("when it fails to match function", () => {
      const FAILURE_MATCH_FUNC = (c: Char) => false;

      it("should not match", () => {
        const matches = lineReader.matchFunc(FAILURE_MATCH_FUNC);

        expect(matches).toBeFalsy();
      });

      it("should not advance", () => {
        lineReader.matchFunc(FAILURE_MATCH_FUNC);

        const position = lineReader.getPosition();
        expect(position).toEqual(INITIAL_POSITION);
      });
    });

    describe("when matching first character successfully", () => {
      const SUCCESS_MATCH_CHAR = LINE[0];

      it("should match", () => {
        const matches = lineReader.match(SUCCESS_MATCH_CHAR);

        expect(matches).toBeTruthy();
      });

      it("should advance", () => {
        lineReader.match(SUCCESS_MATCH_CHAR);

        const position = lineReader.getPosition();
        expect(position).toEqual(INITIAL_POSITION + 1);
      });
    });

    describe("when it fails to match char", () => {
      const FAILURE_MATCH_CHAR = LINE[2];

      it("should not match", () => {
        const matches = lineReader.match(FAILURE_MATCH_CHAR);

        expect(matches).toBeFalsy();
      });

      it("should not advance", () => {
        lineReader.match(FAILURE_MATCH_CHAR);

        const linePosition = lineReader.getPosition();
        expect(linePosition).toEqual(INITIAL_POSITION);
      });
    });

    describe("when matching sequence succesfully", () => {
      const SUCCESS_MATCH_SEQUENCE = ["h", "e", "l", "l"];

      it("should advance by the number of chars matched", () => {
        lineReader.matchSequence(...SUCCESS_MATCH_SEQUENCE);

        const position = lineReader.getPosition();
        expect(position).toEqual(INITIAL_POSITION + SUCCESS_MATCH_SEQUENCE.length);
      });

      it("should match", () => {
        const matches = lineReader.matchSequence(...SUCCESS_MATCH_SEQUENCE);

        expect(matches).toBeTruthy();
      });
    });

    describe("when it fails to match sequence", () => {
      const FAILURE_MATCH_SEQUENCE = ["h", "e", "l", "p"];

      it("should not match", () => {
        const matches = lineReader.matchSequence(...FAILURE_MATCH_SEQUENCE);

        expect(matches).toBeFalsy();
      });

      it("should not advance", () => {
        lineReader.matchSequence(...FAILURE_MATCH_SEQUENCE);

        const position = lineReader.getPosition();
        expect(position).toEqual(INITIAL_POSITION);
      });
    });

  });

  describe("given line reader at end of line", () => {
    beforeAll(() => {
      lineReader = LineReader.from("1");
      lineReader.advance();
    });

    it("should be at end", () => {
      expect(lineReader.isAtEnd()).toBeTruthy();
    });
  });

  describe("given line reader at a certain position", () => {
    const POSITION = 3;
    const LINE = "bla1234";

    beforeEach(() => {
      lineReader = LineReader.from(LINE);
      lineReader.advance();
      lineReader.advance();
      lineReader.advance();
    });

    it("should peek char at position", () => {
      const expectedPeekedChar = LINE[POSITION];

      const peekedChar = lineReader.peek();

      expect(peekedChar).toEqual(expectedPeekedChar);
    });

    it("should match remaining sequence of characters", () => {
      const allMatch = lineReader.matchSequence("1", "2", "3");

      expect(allMatch).toBeTruthy();
    });

    it("should not be at end", () => {
      expect(lineReader.isAtEnd()).toBeFalsy();
    });

    it("should extract all characters before current position", () => {
      const expectedExtractedCharacters = "bla";
      const extractedCharacters = lineReader.extract();

      expect(extractedCharacters).toEqual(expectedExtractedCharacters);
    });
  });
});
