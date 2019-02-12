import { Coordinate } from "../Coordinate";
import { Chars } from "./Token";

export enum TokenType {
  // Values are irrelevant, only to help understand
  // which lexeme represents what

  META_START = "#",
  IMPLEMENTATION = "->",
  BODY_DECLARATION = "::",
  LEFT_PAREN = "(",
  RIGHT_PAREN = ")",

  WORD = "WORD",
  NUMBER = "NUMBER",
  STRING = "STRING",
}

export class ParsedToken {

  constructor(
    private readonly rawValue: string,
    private readonly parsedValue: string | number,
    private readonly type: TokenType,
    private readonly coordinate: Coordinate,
  ) {}

  public toString() {
    return `[${this.type.toString()}: ${this.parsedValue}]`;
  }
}
