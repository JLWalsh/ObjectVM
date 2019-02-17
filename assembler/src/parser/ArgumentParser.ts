import {Argument, ArgumentType} from '../language/domain/Argument';
import {SyntaxError} from '../tokenizer/SyntaxError';

import {ParseError} from './ParseError';
import {TokenReader} from './TokenReader';

export interface ArgumentParser {
  parse(tokenReader: TokenReader): Argument|ParseError;
}