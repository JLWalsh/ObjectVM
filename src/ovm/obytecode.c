#include "obytecode.h"
#include "omath.h"

void *obytecode_read(OSTATE *ovm, size_t read_size)
{
  void *ptr = (void *)&ovm->bytecode[ovm->bytecode_ptr];
  ovm->bytecode_ptr += read_size;

  return ptr;
}

OVMOP obytecode_read_op(OSTATE *ovm)
{
  OVMOP op = *((OVMOP *)obytecode_read(ovm, sizeof(OVMOP)));

  return op;
}

OVMOP obytecode_read_uint(OSTATE *ovm)
{
  OVMUINT uint = *((OVMUINT *)obytecode_read(ovm, sizeof(OVMUINT)));

#ifdef VM_IS_LITTLE_ENDIAN
  uint = (OVMUINT)omath_int16_endian_swap(uint);
#endif

  return uint; // TODO endian flip if required
}
