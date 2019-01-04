#include "obytecode.h"
#include "ovmmath.h"

void *obytecode_read(OVMSTATE *ovm, size_t read_size)
{
  void *ptr = (void *)&ovm->bytecode[ovm->bytecode_ptr];
  ovm->bytecode_ptr += read_size;

  return ptr;
}

OVMOP obytecode_read_op(OVMSTATE *ovm)
{
  OVMOP op = *((OVMOP *)obytecode_read(ovm, sizeof(OVMOP)));

  return op;
}

OVMOP obytecode_read_uint(OVMSTATE *ovm)
{
  OVMUINT uint = *((OVMUINT *)obytecode_read(ovm, sizeof(OVMUINT)));

#ifdef VM_IS_LITTLE_ENDIAN
  uint = (OVMUINT)ovmmath_int16_endian_swap(uint);
#endif

  return uint; // TODO endian flip if required
}
