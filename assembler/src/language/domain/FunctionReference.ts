import {ClassObjectReference} from "./ClassObjectReference";
import {ClassFunction} from "./Function";

abstract class FunctionReference {
  constructor(protected readonly numberOfArguments: number) {}
}

export class ClassObjectFunctionReference extends FunctionReference {
  constructor(
      private readonly classReference: ClassObjectReference,
      private readonly id: number,
      numberOfArguments: number,
  ) {
    super(numberOfArguments);
  }
}

export class GlobalFunctionReference extends FunctionReference {
  constructor(
      private readonly bytecodePosition: number, numberOfArguments: number) {
    super(numberOfArguments);
  }
}
