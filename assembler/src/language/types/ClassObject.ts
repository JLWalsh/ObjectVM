import {IncrementalNumberGenerator} from '../../utils/IncrementalNumberGenerator';

import {ClassObjectReference} from './ClassObjectReference';
import {NoSuchFunctionError} from './errors/NoSuchFunctionError';
import {StaticFunction} from './Function';
import {ClassObjectFunctionReference} from './FunctionReference';

export class ClassObject {
  private readonly generatedFunctionIds: Map<StaticFunction, number>;
  private readonly idGenerator: IncrementalNumberGenerator;

  constructor(
      private readonly name: string,
      private readonly reference: ClassObjectReference,
      private readonly functions: StaticFunction[],
      private readonly classImplementations: ClassObject[],
  ) {
    this.generatedFunctionIds = new Map();
    this.idGenerator = new IncrementalNumberGenerator();
  }

  public buildReferenceFor(functionName: string): ClassObjectFunctionReference {
    const functionFound = this.functions.find(f => f.isNamed(functionName));
    if (!functionFound) {
      throw new NoSuchFunctionError(functionName, this);
    }

    const id = this.generateFunctionIdFor(functionFound);
    return new ClassObjectFunctionReference(
        this.reference, id, functionFound.getNumberOfArguments());
  }

  private generateFunctionIdFor(staticFunction: StaticFunction): number {
    const existingId = this.generatedFunctionIds.get(staticFunction);
    if (existingId) {
      return existingId;
    }

    const id = this.idGenerator.generateNext();
    this.generatedFunctionIds.set(staticFunction, id);

    return id;
  }
}
