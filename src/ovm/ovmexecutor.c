#include "ovmexecutor.h"
#include "ovm.h"
#include "ovmbytecode.h"

void ovmexecutor_init_all() {
  EXECUTORS[OP_INVOKE] = ovmexecutor_invoke;
  EXECUTORS[OP_INVOKE_SUPER] = ovmexecutor_invoke_super;
  EXECUTORS[OP_RETURN] = ovmexecutor_return;
  EXECUTORS[OP_UI_PUSH] = ovmexecutor_ui_push;
  EXECUTORS[OP_UI_PRINT] = ovmexecutor_ui_print;
  EXECUTORS[OP_HALT] = ovmexecutor_halt;
}

void ovmexecutor_return(OVMSTATE *ovm) { ovm_return(ovm); }

void ovmexecutor_halt(OVMSTATE *ovm) { ovm_exit(ovm, 0); }

void ovmexecutor_invoke(OVMSTATE *ovm) {
#ifdef VM_STRICT_MODE
  if (object_id >= vm->num_objects) {
    ovm_throw(ovm, "Invoked method on object id out of range.");
  }
#endif

  OVMID obj_id = ovmbytecode_read_uint(ovm);
  OVMID method_id = ovmbytecode_read_uint(ovm);
  OVMUINT num_args = ovmbytecode_read_uint(ovm);

  ovm->this = ovmstack_pop(&ovm->stack).ptr_val;
  OVMPTR bytecode_ptr =
      ovmobject_resolve_method(&ovm->objects[obj_id], method_id);

  ovm_call(ovm, bytecode_ptr, num_args);
}

void ovmexecutor_invoke_super(OVMSTATE *ovm) {
#ifdef VM_STRICT_MODE
  if (object_id >= vm->num_objects) {
    ovm_throw(ovm, "Invoked super method on object id out of range.");
  }
#endif

  OVMID obj_id = ovmbytecode_read_uint(ovm);
  OVMID method_id = ovmbytecode_read_uint(ovm);
  OVMUINT num_args = ovmbytecode_read_uint(ovm);

  ovm->this = ovmstack_pop(&ovm->stack).ptr_val;
  OVMPTR bytecode_ptr =
      ovmobject_base_resolve_method(&ovm->objects[obj_id], method_id);

  ovm_call(ovm, bytecode_ptr, num_args);
}

void ovmexecutor_local_load(OVMSTATE *ovm) {
  OVMUINT offset = ovmbytecode_read_uint(ovm);

  OVMSTACK_OBJECT local = ovmstack_at(&ovm->stack, ovm->frame_ptr + offset);

  ovmstack_push(&ovm->stack, local);
}
