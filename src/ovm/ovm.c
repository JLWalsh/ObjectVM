#include "ovm.h"
#include "ovmexecutor.h"
#include "ovmstack.h"
#include <stdlib.h>

void ovm_init() { ovmexecutor_init_all(); }

OVMSTATE ovm_create(uint16_t stack_size)
{
  OVMSTATE ovm;
  ovm.num_objects = 0;
  ovm.objects = NULL;
  ovm.this = OVM_NULL;
  ovm.stack = ovmstack_create(stack_size);

  return ovm;
}

void ovm_free(OVMSTATE *ovm) { ovmstack_free(&ovm->stack); }

void ovm_run(OVMSTATE *ovm, void *program)
{
  while (ovm->running)
  {
  }
}

void ovm_load_object(OVMSTATE *ovm, OVMOBJECT o)
{
  ovm->num_objects++;
  ovm->objects = realloc(ovm->objects, sizeof(OVMOBJECT) * ovm->num_objects);
  ovm->objects[ovm->num_objects - 1] = o;
}

void ovm_throw(OVMSTATE *ovm, char *err)
{
  printf("Exception encountered: %s", err);

  exit(1);
}

void ovm_call(OVMSTATE *ovm, OVMPTR bytecode_ptr, OVMUINT num_args)
{
  OVMPTR return_ptr = ovm->bytecode_ptr;
  OVMPTR frame_ptr = ovm->frame_ptr;

  ovm->bytecode_ptr = bytecode_ptr;
  ovm->frame_ptr = ovmstack_ptr(&ovm->frame_ptr) - num_args;

  ovmstack_push(&ovm->stack, ovmstack_obj_of_uint(num_args));
  ovmstack_push(&ovm->stack, ovmstack_obj_of_ptr(return_ptr));
  ovmstack_push(&ovm->stack, ovmstack_obj_of_ptr(frame_ptr));
}
