import {Coordinate} from '../../Coordinate';
import {SyntaxError} from '../SyntaxError';
import {TokenizedLine} from '../TokenizedLine';
import {TokenizedProgram} from '../TokenizedProgram';

describe('TokenizedProgram', () => {
  const ERROR = new SyntaxError('', Coordinate.zero());

  let program: TokenizedProgram;

  describe('a program with errors', () => {
    beforeAll(() => {
      const lineWithErrors = new TokenizedLine('', [], 0, [ERROR]);
      program = new TokenizedProgram([lineWithErrors]);
    });

    it('should have errors', () => {
      const hasErrors = program.hasErrors();

      expect(hasErrors).toBeTruthy();
    });
  });

  describe('a program no errors', () => {
    beforeAll(() => {
      const line = new TokenizedLine('', [], 0, []);
      program = new TokenizedProgram([line]);
    });

    it('should have errors', () => {
      const hasErrors = program.hasErrors();

      expect(hasErrors).toBeFalsy();
    });
  });
});
