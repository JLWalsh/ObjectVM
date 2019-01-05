#ifndef OOBJECT_H
#define OOBJECT_H

#include "otypes.h"
#include "odictionary.h"
#include <stdint.h>

typedef struct OOBJECT_FUNC_TABLE_T
{
  OVM_PTR *func_ptrs;
  uint8_t num_funcs;
} OOBJECT_FUNC_TABLE;

typedef struct OOBJECT_T
{
  OOBJECT_FUNC_TABLE funcs;
  ODICTIONARY vfuncs;
  struct OBMOBJECT_T *base;
  uint64_t mem_size;
} OOBJECT;

OVM_PTR oobject_resolve_method(OOBJECT *o, OVM_UINT method_id);

OVM_PTR oobject_base_resolve_method(OOBJECT *o, OVM_UINT method_id);

OVM_PTR oobject_virtual_resolve_method(OOBJECT *o, OVM_UINT vinterface_id,
                                       OVM_UINT method_id);

void oobject_free(OOBJECT *o);

#endif /* OOBJECT_H */
