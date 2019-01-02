#ifndef OVMSTATE_H
#define OVMSTATE_H

#include "ovmobject.h"
#include <stdint.h>

typedef struct OVMSTATE_T {
  OVMOBJECT *objects;
  uint8_t num_objects;
} OVMSTATE;

#endif /* OVMSTATE_H */
