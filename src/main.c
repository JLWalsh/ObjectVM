#include <malloc.h>
#include <ovm/ovm.h>
#include <ovm/ovmops.h>
#include <stdio.h>

int main(int argc, const char *argv[])
{
  char exe[] = {
      OP_HALT,
      // MAIN
      OP_NEW, 1,                      // B is type 1
      OP_UI_PUSH, 2, OP_INVOKE, 1, 0, // Invoke B::new(int)
      OP_INVOKE, 1, 1, 0,             // Invoke B::doPrint
      OP_HALT,

      // B::new(int)
      OP_LOCAL_LOAD, 0,   // Load arg 0 as int
      OP_GLOBAL_STORE, 0, // Store int at ptr 0 into heap memory
      OP_RETURN,

      // B::doPrint
      OP_GLOBAL_LOAD, 0, // Load A as int
      OP_UI_PRINT, OP_RETURN};

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

  ovm_init();

  OVMSTATE ovm = ovm_create(10, &exe, sizeof(exe));

  ovm_load_object(&ovm, a);
  ovm_load_object(&ovm, b);

  ovm_run(&ovm);

  ovm_free(&ovm);

  ovmobject_free(&a);
  ovmobject_free(&b);

  return 0;
}