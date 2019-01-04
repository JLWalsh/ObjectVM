#ifndef OOBJECT_H
#define OOBJECT_H

#include "otypes.h"
#include <stdint.h>

typedef struct OOBJECT_FUNC_TABLE_T {
  OVMPTR *func_ptrs;
  uint8_t num_funcs;
} OOBJECT_FUNC_TABLE;

typedef struct OOBJECT_T {
  OOBJECT_FUNC_TABLE funcs;
  OOBJECT_FUNC_TABLE *vfuncs;
  uint8_t num_vfunc_tables;
  struct OBMOBJECT_T *base;
  uint64_t mem_size;
} OOBJECT;

OVMPTR oobject_resolve_method(OOBJECT *o, OVMUINT method_id);

OVMPTR oobject_base_resolve_method(OOBJECT *o, OVMUINT method_id);

OVMPTR oobject_interface_resolve_method(OOBJECT *o, OVMUINT interface_id,
                                        OVMUINT method_id);

void oobject_free(OOBJECT *o);

#endif /* OOBJECT_H */
