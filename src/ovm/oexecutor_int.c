#include "oexecutor_int.h"
#include "obytecode.h"
#include "oobject.h"
#include <stdio.h>
#include <string.h>

void oexecutor_ui_push(OSTATE *ovm)
{
  OVM_UINT uint = obytecode_read_uint(ovm);

  ostack_push(&ovm->stack, ostack_obj_of_uint(uint));
}

void oexecutor_ui_print(OSTATE *ovm)
{
  OVM_UINT uint = ostack_pop(&ovm->stack).uint_val;
  printf("%u\n", uint);
}

void oexecutor_ui_global_load(OSTATE *ovm)
{
  OVM_UINT offset = obytecode_read_uint(ovm);
  OVM_PTR this_ref = ostack_at(&ovm->stack, ovm->frame_ptr).ptr_val;

  char *obj_data_ptr = oobject_data_start(omemory_at(&ovm->memory, this_ref));

  OVM_UINT uint = *((OVM_UINT *)&obj_data_ptr[offset]);

  ostack_push(&ovm->stack, ostack_obj_of_uint(uint));
}

void oexecutor_ui_global_store(OSTATE *ovm)
{
  OVM_UINT offset = obytecode_read_uint(ovm);
  OVM_UINT uint = ostack_pop(&ovm->stack).uint_val;

  OVM_PTR this_ref = ostack_at(&ovm->stack, ovm->frame_ptr).ptr_val;
  char *obj_data_ptr = oobject_data_start(omemory_at(&ovm->memory, this_ref));

  memcpy(&obj_data_ptr[offset], &uint, sizeof(OVM_UINT));
}
