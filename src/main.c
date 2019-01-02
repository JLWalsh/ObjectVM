#include <malloc.h>
#include <ovm/ovm.h>
#include <stdio.h>

int main(int argc, const char *argv[]) {
  OVMOBJECT_FUNC_TABLE a_table;
  a_table.num_funcs = 1;
  a_table.func_ptrs = (OVMPTR *)malloc(sizeof(OVMPTR) * 1);
  a_table.func_ptrs[0] = 27;

  OVMOBJECT a;
  a.base = NULL;
  a.funcs = a_table;
  a.vfuncs = NULL;
  a.num_vfunc_tables = 0;

  OVMOBJECT_FUNC_TABLE b_table;
  b_table.num_funcs = 1;
  b_table.func_ptrs = (OVMPTR *)malloc(sizeof(OVMPTR) * 1);
  b_table.func_ptrs[0] = 42;

  OVMOBJECT b;
  b.base = &a;
  b.funcs = b_table;
  b.vfuncs = NULL;
  b.num_vfunc_tables = 0;

  printf("Func 0 of A is %u\n", ovmobject_resolve_method(&a, 0));
  printf("Func 0 of B is %u\n", ovmobject_resolve_method(&b, 0));
  printf("Func 0 of B's parent is %u\n", ovmobject_base_resolve_method(&b, 2));

  return 0;
}