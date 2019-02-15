import { readFileSync } from "fs";
import { Parser } from "./parser/Parser";
import { Program } from "./language/Program";
import { Tokenizer } from "./tokenizer/Tokenizer";

const programSource = readFileSync("./programs/example.oasm", {
  encoding: "utf8",
});
const program = Program.fromString(programSource);

const tokenizedProgram = new Tokenizer().tokenize(program);

const parsedProgram = new Parser().parse(tokenizedProgram);

console.warn(parsedProgram);
