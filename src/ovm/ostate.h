#ifndef OSTATE_H
#define OSTATE_H

#include "omemory.h"
#include "oobject.h"
#include "ostack.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct OSTATE_T
{
  OOBJECT *objects;
  uint8_t num_objects;
  OVMPTR this;
  OVMPTR bytecode_ptr;
  char *bytecode;
  uint64_t bytecode_length;
  OVMPTR frame_ptr;
  OSTACK stack;
  OMEMORY memory;
} OSTATE;

#endif /* OSTATE_H */
