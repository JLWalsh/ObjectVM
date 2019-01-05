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

OVM_PTR oobject_virtual_resolve_method(OOBJECT *o, OVM_UINT vinterface_id,
                                       OVM_UINT method_id)
{
  ODICTIONARY_VALUE key = {.uint_val = vinterface_id};
  ODICTIONARY_ENTRY *entry_found = odictionary_lookup(&o->vfuncs, key);

#ifdef VM_STRICT_MODE
  if (entry_found == NULL)
  {
    return OVM_NULL;
  }
#endif

  OOBJECT_FUNC_TABLE *vfunc_table_for_interface = (OOBJECT_FUNC_TABLE *)entry_found->value.ptr_val;
#ifdef VM_STRICT_MODE
  if (method_id >= vfunc_table_for_interface->num_funcs)
  {
    return OVM_NULL;
  }
#endif
  return vfunc_table_for_interface->func_ptrs[method_id];
}

void oobject_free(OOBJECT *o) { odictionary_free(&o->vfuncs); }