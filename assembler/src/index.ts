import {readFileSync} from 'fs';

import {Parser} from './parser/Parser';
import {Program} from './tokenizer/ProgramSource';
import {Tokenizer} from './tokenizer/Tokenizer';

const programSource = readFileSync('./programs/example.oasm', {
  encoding: 'utf8',
});
const program = Program.fromString(programSource);

const tokenizedProgram = new Tokenizer().tokenize(program);
tokenizedProgram.getErrors().forEach(e => {
  console.warn(e.toString());
});

// const parsedProgram =
// Parser.withDefaultInstructions().parse(tokenizedProgram);
// console.warn(parsedProgram);
