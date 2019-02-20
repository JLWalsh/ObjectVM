import {ClassObject} from '../ClassObject';

export class NoSuchFunctionError {
  constructor(
      private readonly functionName: string,
      private readonly inClass?: ClassObject,
  ) {}
}