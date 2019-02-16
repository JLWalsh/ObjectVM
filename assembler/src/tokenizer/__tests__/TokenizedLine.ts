import {Coordinate} from '../../Coordinate';
import {SyntaxError} from '../SyntaxError';
import {TokenizedLine} from '../TokenizedLine';

describe('TokenizedLine', () => {
  let line: TokenizedLine;

  describe('a line with errors', () => {
    beforeAll(() => {
      const error = new SyntaxError('An error message', Coordinate.zero());
      line = new TokenizedLine('', [], 0, [error]);
    });

    it('should have errors', () => {
      const hasErrors = line.hasErrors();

      expect(hasErrors).toBeTruthy();
    });
  });

  describe('a line without errors', () => {
    beforeAll(() => {
      line = new TokenizedLine('', [], 0, []);
    });

    it('should not have errors', () => {
      const hasErrors = line.hasErrors();

      expect(hasErrors).toBeFalsy();
    });
  });
});
