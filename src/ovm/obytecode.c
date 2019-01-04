#include "obytecode.h"
#include "omath.h"

void *obytecode_read(OSTATE *ovm, size_t read_size)
{
  void *ptr = (void *)&ovm->bytecode[ovm->bytecode_ptr];
  ovm->bytecode_ptr += read_size;

  return ptr;
}

OVM_OP obytecode_read_op(OSTATE *ovm)
{
  OVM_OP op = *((OVM_OP *)obytecode_read(ovm, sizeof(OVM_OP)));

  return op;
}

OVM_OP obytecode_read_uint(OSTATE *ovm)
{
  OVM_UINT uint = *((OVM_UINT *)obytecode_read(ovm, sizeof(OVM_UINT)));

#ifdef VM_IS_LITTLE_ENDIAN
  uint = (OVM_UINT)omath_int16_endian_swap(uint);
#endif

  return uint; // TODO endian flip if required
}
