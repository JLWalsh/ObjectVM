import {Range} from '../Range';

describe('Range', () => {
  let range: Range;

  describe('given number between from and to', () => {
    it('should be contained by range', () => {
      range = Range.fromTo(0, 10);

      const isContained = range.contains(5);

      expect(isContained).toBeTruthy();
    });
  });

  describe('given number before from', () => {
    it('should not be contained by range', () => {
      range = Range.fromTo(0, 10);

      const isContained = range.contains(-2);

      expect(isContained).toBeFalsy();
    });
  });

  describe('given number same as from', () => {
    it('should be contained in range', () => {
      range = Range.fromTo(4, 10);

      const isContained = range.contains(4);

      expect(isContained).toBeTruthy();
    });
  });

  describe('given number after to', () => {
    it('should not be contained by range', () => {
      range = Range.fromTo(0, 10);

      const isContained = range.contains(32);

      expect(isContained).toBeFalsy();
    });
  });

  describe('given number same as to', () => {
    it('should be contained in range', () => {
      range = Range.fromTo(0, 10);

      const isContained = range.contains(10);

      expect(isContained).toBeTruthy();
    });
  });
});