import { Coordinate } from "../Coordinate";
import { Token } from "./Token";

export enum LexemeType {
  // Values are irrelevant, only to help understand
  // which lexeme represents what

  META_START = "#",
  IMPLEMENTATION = "->",
  BODY_DECLARATION = "::",
  LEFT_PAREN = "(",
  RIGHT_PAREN = ")",

  WORD = "WORD",
  NUMBER = "NUMBER",
}

export class Lexeme {

  constructor(
    private readonly rawValue: string,
    private readonly type: LexemeType,
    private readonly coordinate: Coordinate,
  ) {}
}
