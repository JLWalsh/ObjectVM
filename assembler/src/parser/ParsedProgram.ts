import {Line} from '../language/Line';

export class ParsedProgram {
  constructor(
      private readonly lines: Line[],
  ) {}
}