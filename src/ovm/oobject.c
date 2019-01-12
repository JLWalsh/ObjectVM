#include "oobject.h"
#include <stdlib.h>

OVM_PTR oobject_virtual_resolve_method(OOBJECT *o, OVM_UINT vinterface_id,
                                       OVM_UINT method_id)
{
  ODICTIONARY_VALUE interface_key = {.uint_val = vinterface_id};
  ODICTIONARY_ENTRY *interface_found =
      odictionary_lookup(&o->vfuncs, interface_key);

#ifdef VM_STRICT_MODE
  if (interface_found == NULL)
  {
    return OVM_NULL;
  }
#endif

  OOBJECT_FUNC_TABLE *func_table =
      (OOBJECT_FUNC_TABLE *)interface_found->value.ptr_val;

  ODICTIONARY_VALUE method_key = {.uint_val = method_id};
  ODICTIONARY_ENTRY *method_found =
      odictionary_lookup(&func_table->func_ptrs, method_key);

#ifdef VM_STRICT_MODE
  if (method_found == NULL)
  {
    return OVM_NULL;
  }
#endif

  return method_found->value.ovm_ptr_val;
}

void oobject_register_interface(OOBJECT *o, OVM_UINT interface_id,
                                OOBJECT_FUNC_TABLE *func_table)
{
  ODICTIONARY_VALUE key = {.uint_val = interface_id};
  ODICTIONARY_VALUE value = {.ptr_val = func_table};

  odictionary_set(&o->vfuncs, key,
                  value); // TODO add check in strict mode to see if set worked
}

void oobject_data_init(OOBJECT *o, void *obj_ptr)
{
  OOBJECT_DATA_HEADER *header = (OOBJECT_DATA_HEADER *)obj_ptr;
  header->obj_id = o->obj_id;
}

char *oobject_data_start(void *obj_ptr)
{
  return (char *)obj_ptr + sizeof(OOBJECT_DATA_HEADER);
}

OVM_UINT oobject_data_get_id(void *obj_ptr)
{
  OOBJECT_DATA_HEADER *header = (OOBJECT_DATA_HEADER *)obj_ptr;

  return header->obj_id;
}

void oobject_free(OOBJECT *o) { odictionary_free(&o->vfuncs); }

void ofunc_table_register_method(OOBJECT_FUNC_TABLE *func_table,
                                 OVM_UINT method_id, OVM_PTR method_ptr)
{
  ODICTIONARY_VALUE method_key = {.uint_val = method_id};
  ODICTIONARY_VALUE value = {.ovm_ptr_val = method_ptr};

  odictionary_set(&func_table->func_ptrs, method_key, value);
}
