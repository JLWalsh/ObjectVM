import { readFileSync } from "fs";
import { Program } from "./Program";
import { Tokenizer } from "./tokenizer/Tokenizer";

const programSource = readFileSync("./programs/example.oasm", {
  encoding: "utf8",
});
const program = Program.fromString(programSource);

const tokenizedLines = new Tokenizer().tokenize(program);

const txt = tokenizedLines.map((t) => t.toString()).join("\n");
console.warn(txt);
