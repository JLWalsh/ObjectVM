import { Opcode } from "../../../language/Opcode";
import { FromEnumOpcodeParser } from "../FromEnumOpcodeParser";

describe("FromEnumOpcodeParser", () => {

  const parser = new FromEnumOpcodeParser();

  it("should parse an existing opcode", () => {
    const opcodeToParse = Opcode.DUP;

    const parsedOpcode = parser.parse(opcodeToParse);

    expect(parsedOpcode).toEqual(Opcode.DUP);
  });

  describe("when parsing non existant opcode", () => {
    it("should return undefined", () => {
      const opcodeToParse = "haha12345";

      const parsedOpcode = parser.parse(opcodeToParse);

      expect(parsedOpcode).toBeUndefined();
    });
  });
});
