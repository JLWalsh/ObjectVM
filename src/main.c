#include <malloc.h>
#include <ovm/omemory.h>
#include <ovm/oops.h>
#include <ovm/ovm.h>
#include <stdio.h>

int main(int argc, const char *argv[])
{
    // Gas Engine has id 0
    // Engine had id 1
    char exe[] = {
        0, // Byte 0 is reserved for OVM_NULL
        // MAIN
        OP_NEW, 0, 0, // GasEngine type = 0
        OP_DUP, OP_UI_PUSH, 0, 3,
        // Invoke GasEngine (0) :: New (0) with 1 argument
        OP_INVOKE_VIRTUAL, 0, 0, 0, 0, 0, 1,
        // Invoke PrintEngineStats with 1 argument
        OP_INVOKE_STATIC, 0, 21, 0, 1, OP_HALT,

        // PRINTENGINESTATS 21
        OP_LOCAL_LOAD, 0, 0, // Load engine reference
        // Invoke Engine (interface #1) :: GetTorque (0) with 0 args
        OP_INVOKE_VIRTUAL, 0, 1, 0, 0, 0, 0, OP_UI_PRINT,
        // Invoke Engine (interface #1) :: PrintSerialCode (1) with 0 args
        OP_INVOKE_VIRTUAL, 0, 1, 0, 1, 0, 0, OP_RETURN_VOID,

        // GASENGINE::NEW 40
        OP_LOCAL_LOAD, 0, 1,      // Load torque variable. Note that variable #0 is the
                                  // object's reference when doing non-static invoke
        OP_UI_GLOBAL_STORE, 0, 0, // Store that at memory space 0
        OP_RETURN_VOID,

        // GASENGINE::GETTORQUE 47
        OP_UI_GLOBAL_LOAD, 0, 0, // Load torque variable from object's memory
        OP_RETURN,

        // GASENGINE::PRINTSERIALCODE 51
        OP_UI_PUSH, 0, 5, OP_UI_PRINT, OP_RETURN_VOID,

        // ENGINE::PRINTSERIALCODE 56
        OP_UI_PUSH, 0, 10, OP_UI_PRINT, OP_RETURN_VOID};

    OOBJECT_FUNC_TABLE engine_funcs = {.func_ptrs = odictionary_create(1)};
    ofunc_table_register_method(&engine_funcs, 0, 55); // Engine::PrintSerialCode

    OOBJECT engine;
    engine.base = NULL;
    engine.mem_size = 0;
    engine.obj_id = 1;
    engine.vfuncs = odictionary_create(1);

    oobject_register_interface(&engine, 1, &engine_funcs); // Engine has id 1

    OOBJECT_FUNC_TABLE gas_engine_funcs = {.func_ptrs = odictionary_create(1)};
    // GasEngine::New. GasEngine::GetTorque is
    // stored in the vfunc table instead
    ofunc_table_register_method(&gas_engine_funcs, 0, 40);

    OOBJECT_FUNC_TABLE gas_engine_vfuncs_for_engine = {.func_ptrs =
                                                           odictionary_create(2)};
    // GasEngine::PrintSerialCode overrides Engine::PrintSerialCode
    ofunc_table_register_method(&gas_engine_vfuncs_for_engine, 1,
                                51); // GasEngine::PrintSerialCode
    ofunc_table_register_method(&gas_engine_vfuncs_for_engine, 0,
                                47); // GasEngine::GetTorque

    OOBJECT gas_engine;
    gas_engine.obj_id = 0;
    gas_engine.mem_size =
        sizeof(OVM_UINT); // Gas engine stores only 1 value, the torque variable
    gas_engine.base = &engine;
    gas_engine.vfuncs = odictionary_create(2);

    oobject_register_interface(&gas_engine, 0,
                               &gas_engine_funcs); // Gas engine has id 0
    oobject_register_interface(&gas_engine, 1,
                               &gas_engine_vfuncs_for_engine); // Engine has id 1

    ovm_init();

    OSTATE ovm = ovm_create(30, &exe, sizeof(exe), 100);

    ovm_load_object(&ovm, gas_engine);

    ovm_run(&ovm);

    ovm_free(&ovm);

    oobject_free(&gas_engine);

    odictionary_free(&gas_engine_funcs.func_ptrs);
    odictionary_free(&gas_engine_vfuncs_for_engine.func_ptrs);
    odictionary_free(&engine_funcs.func_ptrs);
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