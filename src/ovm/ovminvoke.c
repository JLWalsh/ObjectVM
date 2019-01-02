#include "ovminvoke.h"
#include "ovm.h"
#include <stdlib.h>

void ovminvoke(OVMSTATE *ovm)
{
#ifdef VM_STRICT_MODE
  if (object_id >= vm->num_objects)
  {
    ovm_throw(ovm, "Invoked method on object id out of range.");
  }
#endif

  OVMID obj_id;
  OVMID method_id;
  OVMUINT num_args;

  ovm->this = ovmstack_pop(&ovm->stack).ptr_val;
  OVMPTR bytecode_ptr = ovmobject_resolve_method(obj_id, method_id);

  ovm_invoke(ovm, bytecode_ptr, num_args);
}

void ovminvoke_super(OVMSTATE *ovm, OVMID object_id, OVMID method_id)
{
#ifdef VM_STRICT_MODE
  if (object_id >= vm->num_objects)
    ovm_throw(ovm, "Invoked super method on object id out of range.");
}
#endif

OVMID obj_id;
OVMID method_id;
OVMUINT num_args;

ovm->this = ovmstack_pop(&ovm->stack).ptr_val;
OVMPTR bytecode_ptr = ovmobject_base_resolve_method(obj_id, method_id);

ovm_invoke(ovm, bytecode_ptr, num_args);
}
