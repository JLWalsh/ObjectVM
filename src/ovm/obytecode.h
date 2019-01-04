#ifndef OBYTECODE_H
#define OBYTECODE_H

#include "ostate.h"
#include <stdlib.h>

void *obytecode_read(OSTATE *ovm, size_t read_size);

OVM_OP obytecode_read_op(OSTATE *ovm);

OVM_OP obytecode_read_uint(OSTATE *ovm);

#endif /* OBYTECODE_H */
