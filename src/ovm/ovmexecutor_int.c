#include "ovmexecutor_int.h"
#include "ovmbytecode.h"
#include <stdio.h>
#include <string.h>

void ovmexecutor_ui_push(OVMSTATE *ovm)
{
  OVMUINT uint = ovmbytecode_read_uint(ovm);

  ovmstack_push(&ovm->stack, ovmstack_obj_of_uint(uint));
}

void ovmexecutor_ui_print(OVMSTATE *ovm)
{
  OVMUINT uint = ovmstack_pop(&ovm->stack).uint_val;
  printf("%u\n", uint);
}

void ovmexecutor_ui_global_load(OVMSTATE *ovm)
{
  OVMUINT offset = ovmbytecode_read_uint(ovm);
  OVMCHUNK *obj_data_chunk = ovmmemory_ovmptr_to_chunk(&ovm->memory, ovm->this);

  char *obj_data_ptr = ovmmemory_chunk_data_ptr(obj_data_chunk);

  OVMUINT uint = *((OVMUINT *)&obj_data_ptr[offset]);

  ovmstack_push(&ovm->stack, ovmstack_obj_of_uint(uint));
}

void ovmexecutor_ui_global_store(OVMSTATE *ovm)
{
  OVMUINT offset = ovmbytecode_read_uint(ovm);
  OVMUINT uint = ovmstack_pop(&ovm->stack).uint_val;

  OVMCHUNK *obj_data_chunk = ovmmemory_ovmptr_to_chunk(&ovm->memory, ovm->this);
  char *obj_data_ptr = ovmmemory_chunk_data_ptr(obj_data_chunk);

  memcpy(&obj_data_ptr[offset], &uint, sizeof(OVMUINT));
}
