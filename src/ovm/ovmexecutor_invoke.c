#include "ovmexecutor_invoke.h"
#include "ovm.h"
#include "ovmbytecode.h"
#include <stdlib.h>

void ovmexecutor_invoke(OVMSTATE *ovm)
{
#ifdef VM_STRICT_MODE
  if (object_id >= vm->num_objects)
  {
    ovm_throw(ovm, "Invoked method on object id out of range.");
  }
#endif

  OVMID obj_id = ovmbytecode_read_uint(ovm);
  OVMID method_id = ovmbytecode_read_uint(ovm);
  OVMUINT num_args = ovmbytecode_read_uint(ovm);

  ovm->this = ovmstack_pop(&ovm->stack).ptr_val;
  OVMPTR bytecode_ptr = ovmobject_resolve_method(obj_id, method_id);

  ovm_call(ovm, bytecode_ptr, num_args);
}

void ovmexecutor_invoke_super(OVMSTATE *ovm)
{
#ifdef VM_STRICT_MODE
  if (object_id >= vm->num_objects)
    ovm_throw(ovm, "Invoked super method on object id out of range.");
}
#endif

OVMID obj_id = ovmbytecode_read_uint(ovm);
OVMID method_id = ovmbytecode_read_uint(ovm);
OVMUINT num_args = ovmbytecode_read_uint(ovm);

ovm->this = ovmstack_pop(&ovm->stack).ptr_val;
OVMPTR bytecode_ptr = ovmobject_base_resolve_method(obj_id, method_id);

ovm_call(ovm, bytecode_ptr, num_args);
}
