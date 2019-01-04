#include "ovmbytecode.h"
#include "ovmmath.h"

void *ovmbytecode_read(OVMSTATE *ovm, size_t read_size) {
  void *ptr = (void *)&ovm->bytecode[ovm->bytecode_ptr];
  ovm->bytecode_ptr += read_size;

  return ptr;
}

OVMOP ovmbytecode_read_op(OVMSTATE *ovm) {
  OVMOP op = *((OVMOP *)ovmbytecode_read(ovm, sizeof(OVMOP)));

  return op;
}

OVMOP ovmbytecode_read_uint(OVMSTATE *ovm) {
  OVMUINT uint = *((OVMUINT *)ovmbytecode_read(ovm, sizeof(OVMUINT)));

#ifdef VM_IS_LITTLE_ENDIAN
  uint = (OVMUINT)ovmmath_int16_endian_swap(uint);
#endif

  return uint; // TODO endian flip if required
}
