#include "ovmexecutor.h"
#include "ovm.h"
#include "ovmbytecode.h"

void ovmexecutor_init_all() {
  EXECUTORS[OP_INVOKE] = ovmexecutor_invoke;
  EXECUTORS[OP_INVOKE_SUPER] = ovmexecutor_invoke_super;
  EXECUTORS[OP_RETURN_VOID] = ovmexecutor_returnvoid;
  EXECUTORS[OP_UI_PUSH] = ovmexecutor_ui_push;
  EXECUTORS[OP_UI_PRINT] = ovmexecutor_ui_print;
  EXECUTORS[OP_UI_GLOBAL_LOAD] = ovmexecutor_ui_global_load;
  EXECUTORS[OP_UI_GLOBAL_STORE] = ovmexecutor_ui_global_store;
  EXECUTORS[OP_HALT] = ovmexecutor_halt;
  EXECUTORS[OP_NEW] = ovmexecutor_new;
  EXECUTORS[OP_LOCAL_LOAD] = ovmexecutor_local_load;
  EXECUTORS[OP_DUP] = ovmexecutor_dup;
}

void ovmexecutor_returnvoid(OVMSTATE *ovm) { ovm_return(ovm); }

void ovmexecutor_halt(OVMSTATE *ovm) { ovm_exit(ovm, 0); }

void ovmexecutor_invoke(OVMSTATE *ovm) {
  OVMID obj_id = ovmbytecode_read_uint(ovm);
#ifdef VM_STRICT_MODE
  if (obj_id >= ovm->num_objects) {
    ovm_throw(ovm, "Invoked method on object id out of range.");
  }
#endif

  OVMID method_id = ovmbytecode_read_uint(ovm);
  OVMUINT num_args = ovmbytecode_read_uint(ovm);

  OVMPTR bytecode_ptr =
      ovmobject_resolve_method(&ovm->objects[obj_id], method_id);

  ovm_call(ovm, bytecode_ptr, num_args);
}

void ovmexecutor_invoke_super(OVMSTATE *ovm) {
  OVMID obj_id = ovmbytecode_read_uint(ovm);
#ifdef VM_STRICT_MODE
  if (obj_id >= ovm->num_objects) {
    ovm_throw(ovm, "Invoked super method on object id out of range.");
  }
#endif

  OVMID method_id = ovmbytecode_read_uint(ovm);
  OVMUINT num_args = ovmbytecode_read_uint(ovm);

  OVMPTR bytecode_ptr =
      ovmobject_base_resolve_method(&ovm->objects[obj_id], method_id);

  ovm_call(ovm, bytecode_ptr, num_args);
}

void ovmexecutor_local_load(OVMSTATE *ovm) {
  OVMUINT offset = ovmbytecode_read_uint(ovm);

  OVMSTACK_OBJECT local = ovmstack_at(&ovm->stack, ovm->frame_ptr + offset);

  ovmstack_push(&ovm->stack, local);
}

void ovmexecutor_new(OVMSTATE *ovm) {
  OVMID obj_id = ovmbytecode_read_uint(ovm);
  OVMOBJECT obj = ovm->objects[obj_id];

  OVMPTR obj_ref = ovmmemory_alloc(&ovm->memory, obj.mem_size);

  ovmstack_push(&ovm->stack, ovmstack_obj_of_ptr(obj_ref));
}

void ovmexecutor_dup(OVMSTATE *ovm) {
  OVMSTACK_OBJECT so = ovmstack_top(&ovm->stack, 1);

  ovmstack_push(&ovm->stack, so);
}
