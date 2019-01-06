#include <malloc.h>
#include <ovm/omemory.h>
#include <ovm/oops.h>
#include <ovm/ovm.h>
#include <stdio.h>

int main(int argc, const char *argv[]) {

  char exe[] = {
      // MAIN
      OP_NEW, 0, 0, // B is type 0
      OP_DUP,       // REF REF
      OP_INVOKE_STATIC, 0, 36, 0,
      0, // calls returnTwo, will provide the value needed for B's constructor
      // OP_UI_PUSH, 0, 3, // for B::new(int)
      // Invoke B::new(int) with 1 arg (int)
      OP_INVOKE, 0, 0, 0, 0, 0, 1,
      // Invoke B::doPrint with 0 args
      OP_INVOKE, 0, 0, 0, 1, 0, 0, OP_HALT,

      // B::new(int)
      OP_LOCAL_LOAD, 0, 1,      // Load arg 0 as int
      OP_UI_GLOBAL_STORE, 0, 0, // Store int at ptr 0 into heap memory
      OP_RETURN_VOID,

      // B::doPrint
      OP_UI_GLOBAL_LOAD, 0, 0, // Load A as int
      OP_UI_PRINT, OP_RETURN_VOID,

      // static returnTwo
      OP_UI_PUSH, 0, 2, OP_RETURN};

  OOBJECT_FUNC_TABLE b_table;
  b_table.num_funcs = 1;
  b_table.func_ptrs = (OVM_PTR *)malloc(sizeof(OVM_PTR) * 2);
  b_table.func_ptrs[0] = 24;
  b_table.func_ptrs[1] = 31;

  OOBJECT b;
  b.base = NULL;
  b.funcs = b_table;
  b.mem_size = sizeof(OVM_UINT);

  ovm_init();

  OSTATE ovm = ovm_create(10, &exe, sizeof(exe), 100);

  ovm_load_object(&ovm, b);

  ovm_run(&ovm);

  ovm_free(&ovm);

  oobject_free(&b);

  return 0;
}