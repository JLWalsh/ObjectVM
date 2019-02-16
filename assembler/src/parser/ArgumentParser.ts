import {Argument, ArgumentType} from '../language/Argument';
import {SyntaxError} from '../tokenizer/SyntaxError';

import {TokenReader} from './TokenReader';

export interface ArgumentParser {
  parse(tokenReader: TokenReader): Argument|SyntaxError;
}