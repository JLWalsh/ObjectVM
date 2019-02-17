import {NoSuchFunctionError} from './errors/NoSuchFunctionError';
import {StaticFunction} from './Function';
import {GlobalFunctionReference} from './FunctionReference';

export class GlobalFunctionContext {
  private readonly functionBytecodePositions: Map<StaticFunction, number>;
  private previousFunctionBytecodeOffset: number;

  constructor(
      private readonly globalFunctions: StaticFunction[],
      initialBytecodeOffset: number,
  ) {
    this.functionBytecodePositions = new Map();
    this.previousFunctionBytecodeOffset = initialBytecodeOffset;
  }

  public buildReferenceFor(functionName: string): GlobalFunctionReference {
    const functionFound =
        this.globalFunctions.find(f => f.isNamed(functionName));
    if (!functionFound) {
      throw new NoSuchFunctionError(functionName);
    }

    const bytecodePosition = this.getBytecodePositionFor(functionFound);

    return new GlobalFunctionReference(
        bytecodePosition, functionFound.getNumberOfArguments());
  }

  private getBytecodePositionFor(staticFunction: StaticFunction): number {
    const positionForFunction =
        this.functionBytecodePositions.get(staticFunction);
    if (positionForFunction) {
      return positionForFunction;
    }

    const position = this.previousFunctionBytecodeOffset;
    this.previousFunctionBytecodeOffset += staticFunction.getBytecodeSize();
    this.functionBytecodePositions.set(staticFunction, position);

    return position;
  }
}