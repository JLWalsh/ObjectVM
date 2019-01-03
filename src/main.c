#include <malloc.h>
#include <ovm/ovm.h>
#include <ovm/ovmmemory.h>
#include <ovm/ovmops.h>
#include <stdio.h>

int main(int argc, const char *argv[])
{
  char exe[] = {                    // MAIN
                OP_NEW, 0,          // B is type 0
                OP_UI_PUSH, 2,      // for B::new(int)
                OP_INVOKE, 0, 0,    // Invoke B::new(int)
                OP_INVOKE, 0, 1, 0, // Invoke B::doPrint with 0 args
                OP_HALT,

                // B::new(int)
                OP_LOCAL_LOAD, 0,      // Load arg 0 as int
                OP_UI_GLOBAL_STORE, 0, // Store int at ptr 0 into heap memory
                OP_RETURN,

                // B::doPrint
                OP_UI_GLOBAL_LOAD, 0, // Load A as int
                OP_UI_PRINT, OP_RETURN};

  OVMOBJECT_FUNC_TABLE b_table;
  b_table.num_funcs = 1;
  b_table.func_ptrs = (OVMPTR *)malloc(sizeof(OVMPTR) * 2);
  b_table.func_ptrs[0] = 12;
  b_table.func_ptrs[1] = 17;

  OVMOBJECT b;
  b.base = NULL;
  b.funcs = b_table;
  b.vfuncs = NULL;
  b.num_vfunc_tables = 0;

  ovm_init();

  OVMSTATE ovm = ovm_create(10, &exe, sizeof(exe), 100);

  ovm_load_object(&ovm, b);

  ovm_run(&ovm);

  ovm_free(&ovm);

  ovmobject_free(&b);

  return 0;
}