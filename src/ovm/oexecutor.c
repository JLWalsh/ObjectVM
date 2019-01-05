#include "oexecutor.h"
#include "obytecode.h"
#include "ovm.h"

void oexecutor_init_all() {
  EXECUTORS[OP_INVOKE] = oexecutor_invoke;
  EXECUTORS[OP_INVOKE_SUPER] = oexecutor_invoke_super;
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

void oexecutor_return_void(OSTATE *ovm) { ovm_return(ovm); }

void oexecutor_halt(OSTATE *ovm) { ovm_exit(ovm, 0); }

void oexecutor_invoke(OSTATE *ovm) {
  OVM_UINT obj_id = obytecode_read_uint(ovm);
#ifdef VM_STRICT_MODE
  if (obj_id >= ovm->num_objects) {
    ovm_throw(ovm, "Invoked method on object id out of range.");
  }
#endif

  OVM_UINT method_id = obytecode_read_uint(ovm);
  OVM_UINT num_args = obytecode_read_uint(ovm);

  OVM_PTR bytecode_ptr =
      oobject_resolve_method(&ovm->objects[obj_id], method_id);

  ovm_call(ovm, bytecode_ptr, num_args);
}

void oexecutor_invoke_virtual(OSTATE *ovm) {
  OVM_UINT interface_id = obytecode_read_uint(ovm);
  OVM_UINT method_id = obytecode_read_uint(ovm);
  OVM_UINT num_args = obytecode_read_uint(ovm);

  OVM_PTR bytecode_ptr =
      oobject_virtual_resolve_method(ovm->this_obj, interface_id, method_id);

  ovm_call(ovm, bytecode_ptr, num_args);
}

void oexecutor_invoke_super(OSTATE *ovm) {
  OVM_UINT obj_id = obytecode_read_uint(ovm);
#ifdef VM_STRICT_MODE
  if (obj_id >= ovm->num_objects) {
    ovm_throw(ovm, "Invoked super method on object id out of range.");
  }
#endif

  OVM_UINT method_id = obytecode_read_uint(ovm);
  OVM_UINT num_args = obytecode_read_uint(ovm);

  OVM_PTR bytecode_ptr =
      oobject_base_resolve_method(&ovm->objects[obj_id], method_id);

  ovm_call(ovm, bytecode_ptr, num_args);
}

void oexecutor_local_load(OSTATE *ovm) {
  OVM_UINT offset = obytecode_read_uint(ovm);

  OSTACK_OBJECT local = ostack_at(&ovm->stack, ovm->frame_ptr + offset);

  ostack_push(&ovm->stack, local);
}

void oexecutor_new(OSTATE *ovm) {
  OVM_UINT obj_id = obytecode_read_uint(ovm);
  OOBJECT obj = ovm->objects[obj_id];

  size_t total_size = obj.mem_size + sizeof(OOBJECT_DATA_HEADER);
  OVM_PTR obj_ref = omemory_alloc(&ovm->memory, total_size);
  oobject_data_init(&obj, omemory_at(&ovm->memory, obj_ref));

  ostack_push(&ovm->stack, ostack_obj_of_ptr(obj_ref));
}

void oexecutor_dup(OSTATE *ovm) {
  OSTACK_OBJECT so = ostack_top(&ovm->stack, 1);

  ostack_push(&ovm->stack, so);
}
