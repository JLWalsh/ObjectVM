import { Char } from "../Char";

describe("Char", () => {
  describe("is alpha", () => {
    it("given whole alphabet, all should be chars", () => {
      const chars = "abcdefghijklmnopqrstwvxyz".split("");

      chars.map(Char.isAlpha)
      .forEach((isAlpha) => expect(isAlpha).toBeTruthy());
    });
  });
});
