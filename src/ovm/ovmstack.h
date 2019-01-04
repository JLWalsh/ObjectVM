#ifndef OVMSTACK_H
#define OVMSTACK_H

#include "ovmtypes.h"
#include <stdint.h>

typedef union OVMSTACK_OBJECT_T {
  OVMPTR ptr_val;
  OVMUINT uint_val;
} OVMSTACK_OBJECT;

typedef struct OVMSTACK_T
{
  uint16_t max_size;
  uint16_t size;
  OVMSTACK_OBJECT *objects;
} OVMSTACK;

OVMSTACK ovmstack_create(uint16_t initial_size);

void ovmstack_free(OVMSTACK *s);

void ovmstack_push(OVMSTACK *s, OVMSTACK_OBJECT o);

OVMSTACK_OBJECT ovmstack_pop(OVMSTACK *s);

OVMSTACK_OBJECT ovmstack_top(OVMSTACK *s, uint8_t offset);

OVMSTACK_OBJECT ovmstack_at(OVMSTACK *s, OVMPTR ptr);

OVMPTR ovmstack_ptr(OVMSTACK *s);

OVMSTACK_OBJECT ovmstack_obj_of_ptr(OVMPTR ptr_val);

OVMSTACK_OBJECT ovmstack_obj_of_uint(OVMUINT uint_val);

#endif /* OVMSTACK_H */
