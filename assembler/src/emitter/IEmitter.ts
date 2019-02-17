
export interface IEmitter<T> {
  emitToBytes(value: T): number;
}