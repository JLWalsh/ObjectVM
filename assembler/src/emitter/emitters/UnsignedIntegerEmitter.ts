import {UnsignedInteger} from '../../language/types/UnsignedInteger';
import {IEmitter} from '../IEmitter';

export class UnsignedIntegerEmitter implements IEmitter<UnsignedInteger> {
  emitToBytes(value: UnsignedInteger): number {
    throw new Error('Method not implemented.');
  }
}