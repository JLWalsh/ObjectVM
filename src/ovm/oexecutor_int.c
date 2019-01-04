#include "oexecutor_int.h"
#include "obytecode.h"
#include <stdio.h>
#include <string.h>

void oexecutor_ui_push(OSTATE *ovm) {
  OVMUINT uint = obytecode_read_uint(ovm);

  ostack_push(&ovm->stack, ostack_obj_of_uint(uint));
}

void oexecutor_ui_print(OSTATE *ovm) {
  OVMUINT uint = ostack_pop(&ovm->stack).uint_val;
  printf("%u\n", uint);
}

void oexecutor_ui_global_load(OSTATE *ovm) {
  OVMUINT offset = obytecode_read_uint(ovm);

  char *obj_data_ptr = omemory_at(&ovm->memory, ovm->this);

  OVMUINT uint = *((OVMUINT *)&obj_data_ptr[offset]);

  ostack_push(&ovm->stack, ostack_obj_of_uint(uint));
}

void oexecutor_ui_global_store(OSTATE *ovm) {
  OVMUINT offset = obytecode_read_uint(ovm);
  OVMUINT uint = ostack_pop(&ovm->stack).uint_val;

  char *obj_data_ptr = omemory_at(&ovm->memory, ovm->this);

  memcpy(&obj_data_ptr[offset], &uint, sizeof(OVMUINT));
}
