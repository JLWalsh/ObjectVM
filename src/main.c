#include <malloc.h>
#include <ovm/omemory.h>
#include <ovm/oops.h>
#include <ovm/ovm.h>
#include <stdio.h>

int main(int argc, const char *argv[])
{
  char exe[] = {                  // MAIN
                OP_NEW, 0, 0,     // B is type 0
                OP_DUP,           // REF REF
                OP_UI_PUSH, 0, 3, // for B::new(int) // REF REF 2
                OP_INVOKE, 0, 0, 0, 0, 0,
                1, // Invoke B::new(int) with 1 arg (int)        // REF
                OP_INVOKE, 0, 0, 0, 1, 0,
                0, // Invoke B::doPrint with 0 args              // -
                OP_HALT,

                // B::new(int)
                OP_LOCAL_LOAD, 0, 0,      // Load arg 0 as int
                OP_UI_GLOBAL_STORE, 0, 0, // Store int at ptr 0 into heap memory
                OP_RETURN_VOID,

                // B::doPrint
                OP_UI_GLOBAL_LOAD, 0, 0, // Load A as int
                OP_UI_PRINT, OP_RETURN_VOID};

  OOBJECT_FUNC_TABLE func_table;
  func_table.func_ptrs = NULL;
  func_table.num_funcs = 0;

  OOBJECT_FUNC_TABLE engine_vfunc_table;
  engine_vfunc_table.func_ptrs = (OVM_PTR *)malloc(sizeof(OVM_PTR) * 1);
  engine_vfunc_table.num_funcs = 1;

  // In this scenario, there is an Engine interface with ID #27 and a static
  // method printEngineState
  OOBJECT gas_engine;
  gas_engine.mem_size = 0;
  gas_engine.obj_id = 0;
  gas_engine.funcs = func_table;
  gas_engine.base = NULL;
  gas_engine.vfuncs = odictionary_create(1);

  ODICTIONARY_VALUE interface_key = {.uint_val = 27};
  ODICTIONARY_VALUE func_table_value = {.ptr_val = &engine_vfunc_table};
  odictionary_set(&gas_engine.vfuncs, interface_key, func_table_value);

  ovm_init();

  OSTATE ovm = ovm_create(10, &exe, sizeof(exe), 100);

  ovm_load_object(&ovm, gas_engine);

  ovm_run(&ovm);

  ovm_free(&ovm);

  oobject_free(&b);

  return 0;
}