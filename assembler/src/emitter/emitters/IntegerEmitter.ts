import {Integer} from '../../language/domain/Integer';

import {IEmitter} from './../IEmitter';

export class IntegerEmitter implements IEmitter<Integer> {
  emitToBytes(value: Integer): number {
    throw new Error('Method not implemented.');
  }
}