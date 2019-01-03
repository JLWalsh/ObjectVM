#include "ovmbytecode.h"

void *ovmbytecode_read(OVMSTATE *ovm, size_t read_size)
{
    void *ptr = (void *)ovm->bytecode[ovm->bytecode_ptr];
    ovm->bytecode_ptr += read_size;

    return ptr;
}

OVMOP ovmbytecode_read_op(OVMSTATE *ovm)
{
    OVMOP op = *((OVMOP *)ovmbytecode_read(ovm, sizeof(OVMOP)));

    return op;
}

OVMOP ovmbytecode_read_uint(OVMSTATE *ovm)
{
    OVMUINT uint = *((OVMUINT *)ovmbytecode_read(ovm, sizeof(OVMUINT)));

    return uint; // TODO endian flip if required
}
