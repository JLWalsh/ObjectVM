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
  OVM_PTR this_ref;
  OOBJECT *this_obj;
  OVM_PTR bytecode_ptr;
  char *bytecode;
  uint64_t bytecode_length;
  OVM_PTR frame_ptr;
  OSTACK stack;
  OMEMORY memory;
} OSTATE;

#endif /* OSTATE_H */
