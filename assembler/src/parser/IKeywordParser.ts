
export interface IKeywordParser<T> {
  parse(value: string): T | void;
}
