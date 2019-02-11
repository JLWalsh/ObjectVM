class Char {

  public static isAlpha(char: string): boolean {
    return ("a" <= char && char <= "z") || ("A" <= char && char <= "Z");
  }

  public static isNumeric(char: string): boolean {
    return ("0" <= char && char <= "9");
  }
}

export default Char;
