import {IEmitter} from './../IEmitter';

type Opcode = number;
export class OpcodeEmitter implements IEmitter<Opcode> {
  emitToBytes(value: number): number {
    throw new Error('Method not implemented.');
  }
}