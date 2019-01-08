#include <stdlib.h>
#include <ovm/omemory.h>
#include <ovm/oops.h>
#include <ovm/ovm.h>
#include <stdio.h>

int main(int argc, const char *argv[])
{

  char exe[] = {
      // MAIN
      OP_NEW, 0, 0, // GasEngine type = 0
      OP_DUP, OP_UI_PUSH, 0, 3,
      // Invoke GasEngine (0) :: New (0) with 1 argument
      OP_INVOKE, 0, 0, 0, 0, 0, 1,
      // Invoke PrintEngineTorque with 1 argument
      OP_INVOKE_STATIC, 0, 20, 0, 1,
      OP_HALT,

      // PRINTENGINETORQUE
      OP_LOCAL_LOAD, 0, 0, // Load engine reference
      // Invoke Engine (interface #0) :: GetTorque (0) with 0 args
      OP_INVOKE_VIRTUAL, 0, 0, 0, 0, 0, 0,
      OP_UI_PRINT,
      OP_RETURN_VOID,

      // GASENGINE::NEW
      OP_LOCAL_LOAD, 0, 1,      // Load torque variable. Note that variable #0 is the
                                // object's reference when doing non-static invoke
      OP_UI_GLOBAL_STORE, 0, 0, // Store that at memory space 0
      OP_RETURN_VOID,

      // GASENGINE::GETTORQUE
      OP_UI_GLOBAL_LOAD, 0, 0, // Load torque variable from object's memory
      OP_RETURN};

  OOBJECT_FUNC_TABLE gas_engine_funcs;
  gas_engine_funcs.func_ptrs = (OVM_PTR *)malloc(sizeof(OVM_PTR) * 1);
  gas_engine_funcs.func_ptrs[0] = 32;
  gas_engine_funcs.num_funcs = 1; // GasEngine::New. GasEngine::GetTorque is
                                  // stored in the vfunc table instead

  OOBJECT_FUNC_TABLE gas_engine_vfuncs_for_engine;
  gas_engine_vfuncs_for_engine.func_ptrs =
      (OVM_PTR *)malloc(sizeof(OVM_PTR) * 1);
  gas_engine_vfuncs_for_engine.func_ptrs[0] = 39;
  gas_engine_vfuncs_for_engine.num_funcs = 1; //  GasEngine::GetTorque

  OOBJECT gas_engine;
  gas_engine.obj_id = 0;
  gas_engine.funcs = gas_engine_funcs;
  gas_engine.mem_size =
      sizeof(OVM_UINT); // Gas engine stores only 1 value, the torque variable
  gas_engine.base = NULL;
  gas_engine.vfuncs = odictionary_create(1);

  ODICTIONARY_VALUE interface_key = {.uint_val =
                                         0}; // Engine interface has id 0
  ODICTIONARY_VALUE value = {.ptr_val = &gas_engine_vfuncs_for_engine};
  odictionary_set(&gas_engine.vfuncs, interface_key, value);

  ovm_init();

  OSTATE ovm = ovm_create(10, &exe, sizeof(exe), 100);

  ovm_load_object(&ovm, gas_engine);

  ovm_run(&ovm);

  ovm_free(&ovm);

  oobject_free(&gas_engine);

  free(gas_engine_funcs.func_ptrs);
  free(gas_engine_vfuncs_for_engine.func_ptrs);
  return 0;
}

// Static call & function calling test program. Should print 2
// char exe[] = {
//     // MAIN
//     OP_NEW, 0, 0, // B is type 0
//     OP_DUP,       // REF REF
//     OP_INVOKE_STATIC, 0, 36, 0,
//     0, // calls returnTwo, will provide the value needed for B's constructor
//     // OP_UI_PUSH, 0, 3, // for B::new(int)
//     // Invoke B::new(int) with 1 arg (int)
//     OP_INVOKE, 0, 0, 0, 0, 0, 1,
//     // Invoke B::doPrint with 0 args
//     OP_INVOKE, 0, 0, 0, 1, 0, 0, OP_HALT,

//     // B::new(int)
//     OP_LOCAL_LOAD, 0, 1,      // Load arg 0 as int
//     OP_UI_GLOBAL_STORE, 0, 0, // Store int at ptr 0 into heap memory
//     OP_RETURN_VOID,

//     // B::doPrint
//     OP_UI_GLOBAL_LOAD, 0, 0, // Load A as int
//     OP_UI_PRINT, OP_RETURN_VOID,

//     // static returnTwo
//     OP_UI_PUSH, 0, 2, OP_RETURN};

// OOBJECT_FUNC_TABLE b_table;
// b_table.num_funcs = 1;
// b_table.func_ptrs = (OVM_PTR *)malloc(sizeof(OVM_PTR) * 2);
// b_table.func_ptrs[0] = 24;
// b_table.func_ptrs[1] = 31;

// OOBJECT b;
// b.base = NULL;
// b.funcs = b_table;
// b.mem_size = sizeof(OVM_UINT);