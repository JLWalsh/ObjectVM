#ifndef OVMOBJECT_H
#define OVMOBJECT_H

#include "ovmtypes.h"
#include <stdint.h>

typedef struct OVMOBJECT_FUNC_TABLE_T {
  OVMPTR *func_ptrs;
  uint8_t num_funcs;
} OVMOBJECT_FUNC_TABLE;

typedef struct OVMOBJECT_T {
  OVMOBJECT_FUNC_TABLE funcs;
  OVMOBJECT_FUNC_TABLE *vfuncs;
  uint8_t num_vfunc_tables;
  struct OBMOBJECT_T *base;
} OVMOBJECT;

OVMPTR ovmobject_resolve_method(OVMOBJECT *o, OVMID method_id);

OVMPTR ovmobject_base_resolve_method(OVMOBJECT *o, OVMID method_id);

OVMPTR ovmobject_interface_resolve_method(OVMOBJECT *o, OVMID interface_id,
                                          OVMID method_id);

void ovmobject_free(OVMOBJECT *o);

#endif /* OVMOBJECT_H */
