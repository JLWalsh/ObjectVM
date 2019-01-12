#include "oexecutor.h"
#include "obytecode.h"
#include "ovm.h"

void oexecutor_init_all()
{
  EXECUTORS[OP_INVOKE_STATIC] = oexecutor_invoke_static;
  EXECUTORS[OP_INVOKE_VIRTUAL] = oexecutor_invoke_virtual;
  EXECUTORS[OP_RETURN] = oexecutor_return;
  EXECUTORS[OP_RETURN_VOID] = oexecutor_return_void;
  EXECUTORS[OP_UI_PUSH] = oexecutor_ui_push;
  EXECUTORS[OP_UI_PRINT] = oexecutor_ui_print;
  EXECUTORS[OP_UI_GLOBAL_LOAD] = oexecutor_ui_global_load;
  EXECUTORS[OP_UI_GLOBAL_STORE] = oexecutor_ui_global_store;
  EXECUTORS[OP_HALT] = oexecutor_halt;
  EXECUTORS[OP_NEW] = oexecutor_new;
  EXECUTORS[OP_LOCAL_LOAD] = oexecutor_local_load;
  EXECUTORS[OP_DUP] = oexecutor_dup;
}

void oexecutor_return(OSTATE *ovm)
{
  OSTACK_OBJECT return_val = ostack_pop(&ovm->stack);

  ovm_return(ovm);

  ostack_push(&ovm->stack, return_val);
}

void oexecutor_return_void(OSTATE *ovm) { ovm_return(ovm); }

void oexecutor_halt(OSTATE *ovm) { ovm_exit(ovm, 0); }

void oexecutor_invoke_virtual(OSTATE *ovm)
{
  OVM_UINT interface_id = obytecode_read_uint(ovm);
  OVM_UINT method_id = obytecode_read_uint(ovm);
  OVM_UINT num_args = obytecode_read_uint(ovm);

  OVM_PTR obj_ref = ostack_top(&ovm->stack, num_args + 1).ptr_val;
  OOBJECT *obj = ovm_object_at(ovm, obj_ref);

  OVM_PTR bytecode_ptr =
      oobject_virtual_resolve_method(obj, interface_id, method_id);

#ifdef VM_STRICT_MODE
  if (bytecode_ptr == OVM_NULL)
  {
    ovm_throw(ovm, "Failed to resolve virtual method. Verify that interface id and method id is correct.");
  }
#endif

  ovm_call(ovm, bytecode_ptr, num_args, obj_ref);
}

void oexecutor_invoke_static(OSTATE *ovm)
{
  OVM_PTR bytecode_ptr = obytecode_read_uint(ovm);
  OVM_PTR num_args = obytecode_read_uint(ovm);

  ovm_call_static(ovm, bytecode_ptr, num_args);
}

void oexecutor_local_load(OSTATE *ovm)
{
  OVM_UINT offset = obytecode_read_uint(ovm);

  OSTACK_OBJECT local = ostack_at(&ovm->stack, ovm->frame_ptr - offset);

  ostack_push(&ovm->stack, local);
}

void oexecutor_new(OSTATE *ovm)
{
  OVM_UINT obj_id = obytecode_read_uint(ovm);
  OOBJECT obj = ovm->objects[obj_id];

  size_t total_size = obj.mem_size + sizeof(OOBJECT_DATA_HEADER);
  OVM_PTR obj_ref = omemory_alloc(&ovm->memory, total_size);
  oobject_data_init(&obj, omemory_at(&ovm->memory, obj_ref));

  ostack_push(&ovm->stack, ostack_obj_of_ptr(obj_ref));
}

void oexecutor_dup(OSTATE *ovm)
{
  OSTACK_OBJECT so = ostack_top(&ovm->stack, 1);

  ostack_push(&ovm->stack, so);
}
