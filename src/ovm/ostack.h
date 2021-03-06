#ifndef OSTACK_H
#define OSTACK_H

#include "otypes.h"
#include <stdint.h>

typedef union OSTACK_OBJECT_T {
  OVM_PTR ptr_val;
  OVM_UINT uint_val;
} OSTACK_OBJECT;

typedef struct OSTACK_T
{
  uint16_t max_size;
  uint16_t size;
  OSTACK_OBJECT *objects;
} OSTACK;

OSTACK ostack_create(uint16_t initial_size);

void ostack_free(OSTACK *s);

void ostack_push(OSTACK *s, OSTACK_OBJECT o);

OSTACK_OBJECT ostack_pop(OSTACK *s);

OSTACK_OBJECT ostack_top(OSTACK *s, uint8_t offset);

OSTACK_OBJECT ostack_at(OSTACK *s, OVM_PTR ptr);

void ostack_to_index(OSTACK *s, OVM_PTR index);

OVM_PTR ostack_index(OSTACK *s);

OSTACK_OBJECT ostack_obj_of_ptr(OVM_PTR ptr_val);

OSTACK_OBJECT ostack_obj_of_uint(OVM_UINT uint_val);

#endif /* OSTACK_H */
