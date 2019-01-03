#ifndef OVMSTATE_H
#define OVMSTATE_H

#include "ovmobject.h"
#include "ovmstack.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct OVMSTATE_T
{
  OVMOBJECT *objects;
  uint8_t num_objects;
  OVMPTR this;
  OVMPTR bytecode_ptr;
  char *bytecode;
  uint64_t bytecode_length;
  OVMPTR frame_ptr;
  OVMSTACK stack;
} OVMSTATE;

#endif /* OVMSTATE_H */
