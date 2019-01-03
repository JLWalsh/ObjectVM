#ifndef OVMBYTECODE_H
#define OVMBYTECODE_H

#include "ovmstate.h"
#include <stdlib.h>

void *ovmbytecode_read(OVMSTATE *ovm, size_t read_size);

OVMOP ovmbytecode_read_op(OVMSTATE *ovm);

OVMOP ovmbytecode_read_uint(OVMSTATE *ovm);

#endif /* OVMBYTECODE_H */
