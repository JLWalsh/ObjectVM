export class Char {

  public static isAlpha(char: string): boolean {
    return ("a" <= char && char <= "z") || ("A" <= char && char <= "Z") || char === "_";
  }

  public static isNumeric(char: string): boolean {
    return ("0" <= char && char <= "9");
  }

  public static isPartOfNumber(char: string): boolean {
    return Char.isNumeric(char) || char === ".";
  }
}
