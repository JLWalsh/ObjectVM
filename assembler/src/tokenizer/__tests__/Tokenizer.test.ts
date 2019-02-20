import {Token, TokenType} from '../ParsedToken';
import {Program} from '../ProgramSource';
import {Tokenizer} from '../Tokenizer';

describe('Tokenizer', () => {
  const tokenizer = new Tokenizer();

  it('should parse multiple tokens', () => {
    const program = createProgram(
        'OP_HELLO 45 274.183 -28.1 "Hello, \\"world!" -> :: // This is a comment');

    const tokens = tokenizer.tokenize(program).getLine(0).getTokens();

    expect(tokens[0].is(TokenType.WORD)).toBeTruthy();
    expect(tokens[0].getParsedValue()).toEqual('OP_HELLO');
    expect(tokens[1].is(TokenType.NUMBER)).toBeTruthy();
    expect(tokens[1].getParsedValue()).toEqual(45);
    expect(tokens[2].is(TokenType.NUMBER)).toBeTruthy();
    expect(tokens[2].getParsedValue()).toEqual(274.183);
    expect(tokens[3].is(TokenType.NUMBER)).toBeTruthy();
    expect(tokens[3].getParsedValue()).toEqual(-28.1);
    expect(tokens[4].is(TokenType.STRING)).toBeTruthy();
    expect(tokens[4].getParsedValue()).toEqual('Hello, "world!');
    expect(tokens[5].is(TokenType.IMPLEMENTATION)).toBeTruthy();
    expect(tokens[6].is(TokenType.BODY_DECLARATION)).toBeTruthy();
  });

  it('should not parse comment', () => {
    const program = createProgram('// this is a comment');

    const parsedLine = tokenizer.tokenize(program).getLine(0);

    expect(parsedLine.getTokens()).toEqual([]);
  });

  it('should parse a word', () => {
    const program = createProgram('aWord');

    const parsedToken = parseSingleToken(program);

    expect(parsedToken.is(TokenType.WORD)).toBeTruthy();
    expect(parsedToken.getParsedValue()).toEqual('aWord');
  });

  it('should parse negated number', () => {
    const program = createProgram('-391');

    const token = parseSingleToken(program);

    expect(token.is(TokenType.NUMBER)).toBeTruthy();
    expect(token.getParsedValue()).toEqual(-391);
  });

  it('should parse number without decimals', () => {
    const program = createProgram('427');

    const parsedToken = parseSingleToken(program);

    expect(parsedToken.is(TokenType.NUMBER)).toBeTruthy();
    expect(parsedToken.getParsedValue()).toEqual(427);
  });

  it('should parse number with decimals', () => {
    const program = createProgram('842.1341');

    const parsedToken = parseSingleToken(program);

    expect(parsedToken.is(TokenType.NUMBER)).toBeTruthy();
    expect(parsedToken.getParsedValue()).toEqual(842.1341);
  });

  it('should parse string', () => {
    const program = createProgram('"Hello, world!"');

    const parsedToken = parseSingleToken(program);

    expect(parsedToken.is(TokenType.STRING)).toBeTruthy();
    expect(parsedToken.getParsedValue()).toEqual('Hello, world!');
  });

  it('should parse escaped string', () => {
    const program = createProgram('"Hello, \\" world!"');

    const parsedToken = parseSingleToken(program);

    expect(parsedToken.is(TokenType.STRING)).toBeTruthy();
    expect(parsedToken.getParsedValue()).toEqual('Hello, " world!');
  });

  it('should parse meta start', () => {
    const program = createProgram('#');

    const parsedToken = parseSingleToken(program);

    expect(parsedToken.is(TokenType.META_START));
  });

  it('should parse implementation', () => {
    const program = createProgram('->');

    const parsedToken = parseSingleToken(program);

    expect(parsedToken.is(TokenType.IMPLEMENTATION)).toBeTruthy();
  });

  it('should parse body declaration', () => {
    const program = createProgram('::');

    const parsedToken = parseSingleToken(program);

    expect(parsedToken.is(TokenType.BODY_DECLARATION)).toBeTruthy();
  });

  it('should parse left paren', () => {
    const program = createProgram('(');

    const parsedToken = parseSingleToken(program);

    expect(parsedToken.is(TokenType.LEFT_PAREN)).toBeTruthy();
  });

  it('should parse right paren', () => {
    const program = createProgram(')');

    const parsedToken = parseSingleToken(program);

    expect(parsedToken.is(TokenType.RIGHT_PAREN)).toBeTruthy();
  });

  function parseSingleToken(program: Program): Token {
    return tokenizer.tokenize(program).getLine(0).getTokens()[0];
  }

  function createProgram(source: string): Program {
    return Program.fromString(source);
  }
});
