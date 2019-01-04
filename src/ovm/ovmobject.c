#include "ovmobject.h"
#include <stdlib.h>

OVMPTR ovmobject_resolve_method(OVMOBJECT *o, uint8_t method_id)
{
#ifdef VM_STRICT_MODE
  if (method_id >= o->funcs.num_funcs)
  {
    return OVM_NULL;
  }
#endif

  return o->funcs.func_ptrs[method_id];
}

OVMPTR ovmobject_base_resolve_method(OVMOBJECT *o, uint8_t method_id)
{
#ifdef VM_STRICT_MODE
  if (o->base == NULL)
  {
    return OVM_NULL;
  }
#endif

  return ovmobject_resolve_method(o->base, method_id);
}

OVMPTR ovmobject_interface_resolve_method(OVMOBJECT *o, uint8_t interface_id,
                                          uint8_t method_id)
{
#ifdef VM_STRICT_MODE
  if (interface_id >= o->num_vfunc_tables)
  {
    return OVM_NULL;
  }

  if (method_id >= o->vfuncs[interface_id].num_funcs)
  {
    return OVM_NULL;
  }
#endif

  return o->vfuncs[interface_id].func_ptrs[method_id];
}

void ovmobject_free(OVMOBJECT *o)
{
  free(o->vfuncs);
  o->vfuncs = NULL;
  o->num_vfunc_tables = 0;
}