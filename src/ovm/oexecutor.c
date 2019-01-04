#include "oexecutor.h"
#include "obytecode.h"
#include "ovm.h"

void oexecutor_init_all()
{
  EXECUTORS[OP_INVOKE] = oexecutor_invoke;
  EXECUTORS[OP_INVOKE_SUPER] = oexecutor_invoke_super;
  EXECUTORS[OP_RETURN_VOID] = oexecutor_returnvoid;
  EXECUTORS[OP_UI_PUSH] = oexecutor_ui_push;
  EXECUTORS[OP_UI_PRINT] = oexecutor_ui_print;
  EXECUTORS[OP_UI_GLOBAL_LOAD] = oexecutor_ui_global_load;
  EXECUTORS[OP_UI_GLOBAL_STORE] = oexecutor_ui_global_store;
  EXECUTORS[OP_HALT] = oexecutor_halt;
  EXECUTORS[OP_NEW] = oexecutor_new;
  EXECUTORS[OP_LOCAL_LOAD] = oexecutor_local_load;
  EXECUTORS[OP_DUP] = oexecutor_dup;
}

void oexecutor_returnvoid(OVMSTATE *ovm) { ovm_return(ovm); }

void oexecutor_halt(OVMSTATE *ovm) { ovm_exit(ovm, 0); }

void oexecutor_invoke(OVMSTATE *ovm)
{
  OVMUINT obj_id = obytecode_read_uint(ovm);
#ifdef VM_STRICT_MODE
  if (obj_id >= ovm->num_objects)
  {
    ovm_throw(ovm, "Invoked method on object id out of range.");
  }
#endif

  OVMUINT method_id = obytecode_read_uint(ovm);
  OVMUINT num_args = obytecode_read_uint(ovm);

  OVMPTR bytecode_ptr =
      ovmobject_resolve_method(&ovm->objects[obj_id], method_id);

  ovm_call(ovm, bytecode_ptr, num_args);
}

void oexecutor_invoke_super(OVMSTATE *ovm)
{
  OVMUINT obj_id = obytecode_read_uint(ovm);
#ifdef VM_STRICT_MODE
  if (obj_id >= ovm->num_objects)
  {
    ovm_throw(ovm, "Invoked super method on object id out of range.");
  }
#endif

  OVMUINT method_id = obytecode_read_uint(ovm);
  OVMUINT num_args = obytecode_read_uint(ovm);

  OVMPTR bytecode_ptr =
      ovmobject_base_resolve_method(&ovm->objects[obj_id], method_id);

  ovm_call(ovm, bytecode_ptr, num_args);
}

void oexecutor_local_load(OVMSTATE *ovm)
{
  OVMUINT offset = obytecode_read_uint(ovm);

  OVMSTACK_OBJECT local = ovmstack_at(&ovm->stack, ovm->frame_ptr + offset);

  ovmstack_push(&ovm->stack, local);
}

void oexecutor_new(OVMSTATE *ovm)
{
  OVMUINT obj_id = obytecode_read_uint(ovm);
  OVMOBJECT obj = ovm->objects[obj_id];

  OVMPTR obj_ref = ovmmemory_alloc(&ovm->memory, obj.mem_size);

  ovmstack_push(&ovm->stack, ovmstack_obj_of_ptr(obj_ref));
}

void oexecutor_dup(OVMSTATE *ovm)
{
  OVMSTACK_OBJECT so = ovmstack_top(&ovm->stack, 1);

  ovmstack_push(&ovm->stack, so);
}
