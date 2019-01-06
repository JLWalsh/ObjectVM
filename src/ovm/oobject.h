#ifndef OOBJECT_H
#define OOBJECT_H

#include "odictionary.h"
#include "otypes.h"
#include <stdint.h>

typedef struct OOBJECT_FUNC_TABLE_T {
  OVM_PTR *func_ptrs;
  uint8_t num_funcs;
} OOBJECT_FUNC_TABLE;

typedef struct OOBJECT_T {
  OVM_UINT obj_id;
  OOBJECT_FUNC_TABLE funcs;
  ODICTIONARY vfuncs;
  struct OBMOBJECT_T *base;
  uint64_t mem_size;
} OOBJECT;

typedef struct OOBJECT_DATA_HEADER_T { OVM_UINT obj_id; } OOBJECT_DATA_HEADER;

OVM_PTR oobject_resolve_method(OOBJECT *o, OVM_UINT method_id);

OVM_PTR oobject_base_resolve_method(OOBJECT *o, OVM_UINT method_id);

OVM_PTR oobject_virtual_resolve_method(OOBJECT *o, OVM_UINT vinterface_id,
                                       OVM_UINT method_id);

void oobject_data_init(OOBJECT *o, void *obj_ptr);

char *oobject_data_start(void *obj_ptr);

OVM_UINT oobject_data_get_id(void *obj_ptr);

void oobject_free(OOBJECT *o);

#endif /* OOBJECT_H */
