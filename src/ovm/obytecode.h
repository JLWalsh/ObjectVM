#ifndef obytecode_H
#define obytecode_H

#include "ovmstate.h"
#include <stdlib.h>

void *obytecode_read(OVMSTATE *ovm, size_t read_size);

OVMOP obytecode_read_op(OVMSTATE *ovm);

OVMOP obytecode_read_uint(OVMSTATE *ovm);

#endif /* obytecode_H */
