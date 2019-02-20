import {NumericOutOfRangeError} from '../errors/NumericOutOfRangeError';
import {Integer} from '../types/Integer';

describe('Integer', () => {
  describe('given integer builder', () => {
    const NUMBER_OF_BITS = 8;
    const MAX_VALUE_FOR_BIT_SIZE = 128;
    const MIN_VALUE_FOR_BIT_SIZE = -127;

    const builder = Integer.withSize(NUMBER_OF_BITS);

    it('should build integer given value in range', () => {
      const integer = builder.createWithValue(32);

      expect(integer.getValue()).toEqual(32);
    });

    it('should build integer given min value', () => {
      const integer = builder.createWithValue(MIN_VALUE_FOR_BIT_SIZE);

      expect(integer.getValue()).toEqual(MIN_VALUE_FOR_BIT_SIZE);
    });

    it('should build integer given max value', () => {
      const integer = builder.createWithValue(MAX_VALUE_FOR_BIT_SIZE);

      expect(integer.getValue()).toEqual(MAX_VALUE_FOR_BIT_SIZE);
    });

    it('should throw NumericOutOfRangeError when value is inferior to min value',
       () => {
         const buildThatShouldThrow = () =>
             builder.createWithValue(MIN_VALUE_FOR_BIT_SIZE - 1);

         expect(buildThatShouldThrow).toThrowError(NumericOutOfRangeError);
       });

    it('should throw NumericOutOfRangeError when value exceeds max value',
       () => {
         const buildThatShouldThrow = () =>
             builder.createWithValue(MAX_VALUE_FOR_BIT_SIZE + 1);

         expect(buildThatShouldThrow).toThrowError(NumericOutOfRangeError);
       });
  });
});
