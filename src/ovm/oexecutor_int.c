#include "oexecutor_int.h"
#include "obytecode.h"
#include <stdio.h>
#include <string.h>

void oexecutor_ui_push(OVMSTATE *ovm)
{
  OVMUINT uint = obytecode_read_uint(ovm);

  ovmstack_push(&ovm->stack, ovmstack_obj_of_uint(uint));
}

void oexecutor_ui_print(OVMSTATE *ovm)
{
  OVMUINT uint = ovmstack_pop(&ovm->stack).uint_val;
  printf("%u\n", uint);
}

void oexecutor_ui_global_load(OVMSTATE *ovm)
{
  OVMUINT offset = obytecode_read_uint(ovm);

  char *obj_data_ptr = ovmmemory_at(&ovm->memory, ovm->this);

  OVMUINT uint = *((OVMUINT *)&obj_data_ptr[offset]);

  ovmstack_push(&ovm->stack, ovmstack_obj_of_uint(uint));
}

void oexecutor_ui_global_store(OVMSTATE *ovm)
{
  OVMUINT offset = obytecode_read_uint(ovm);
  OVMUINT uint = ovmstack_pop(&ovm->stack).uint_val;

  char *obj_data_ptr = ovmmemory_at(&ovm->memory, ovm->this);

  memcpy(&obj_data_ptr[offset], &uint, sizeof(OVMUINT));
}
