#include "oobject.h"
#include <stdlib.h>

OVM_PTR oobject_resolve_method(OOBJECT *o, OVM_UINT method_id)
{
#ifdef VM_STRICT_MODE
  if (method_id >= o->funcs.num_funcs)
  {
    return OVM_NULL;
  }
#endif

  return o->funcs.func_ptrs[method_id];
}

OVM_PTR oobject_base_resolve_method(OOBJECT *o, OVM_UINT method_id)
{
#ifdef VM_STRICT_MODE
  if (o->base == NULL)
  {
    return OVM_NULL;
  }
#endif

  return oobject_resolve_method(o->base, method_id);
}

OVM_PTR oobject_interface_resolve_method(OOBJECT *o, OVM_UINT interface_id,
                                         OVM_UINT method_id)
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

void oobject_free(OOBJECT *o)
{
  free(o->vfuncs);
  o->vfuncs = NULL;
  o->num_vfunc_tables = 0;
}