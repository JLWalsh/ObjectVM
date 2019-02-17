import {IntegerOutOfRangeError} from '../errors/IntegerOutOfRangeError';
import {UnsignedInteger} from '../UnsignedInteger';

describe('UnsignedInteger', () => {
  describe('given unsigned integer builder', () => {
    const NUMBER_OF_BITS = 8;
    const MAX_VALUE_FOR_BIT_SIZE = 255;
    const MIN_VALUE_FOR_BIT_SIZE = 0;

    const builder = UnsignedInteger.withSize(NUMBER_OF_BITS);

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

    it('should throw IntegerOutOfRangeError when value is inferior to min value',
       () => {
         const buildThatShouldThrow = () =>
             builder.createWithValue(MIN_VALUE_FOR_BIT_SIZE - 1);

         expect(buildThatShouldThrow).toThrowError(IntegerOutOfRangeError);
       });

    it('should throw IntegerOutOfRangeError when value exceeds max value',
       () => {
         const buildThatShouldThrow = () =>
             builder.createWithValue(MAX_VALUE_FOR_BIT_SIZE + 1);

         expect(buildThatShouldThrow).toThrowError(IntegerOutOfRangeError);
       });
  });
});