#include "ovm.h"
#include "obytecode.h"
#include "oexecutor.h"
#include "ovmstack.h"
#include <stdio.h>
#include <stdlib.h>

void ovm_init() { oexecutor_init_all(); }

OVMSTATE ovm_create(uint16_t stack_size, char *bytecode,
                    uint64_t bytecode_length, uint64_t initial_heap_size)
{
  OVMSTATE ovm;
  ovm.num_objects = 0;
  ovm.objects = NULL;
  ovm.this = OVM_NULL;
  ovm.stack = ovmstack_create(stack_size);
  ovm.frame_ptr = 0;

  ovm.bytecode = bytecode;
  ovm.bytecode_length = bytecode_length;
  ovm.bytecode_ptr = 0;

  ovm.memory = ovmmemory_create(initial_heap_size);

  return ovm;
}

void ovm_free(OVMSTATE *ovm)
{
  ovmstack_free(&ovm->stack);
  ovmmemory_free(&ovm->memory);
}

void ovm_run(OVMSTATE *ovm)
{
  for (;;)
  {
    OVMOP op = obytecode_read_op(ovm);

    EXECUTORS[op](ovm);
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
  printf("Exception encountered: %s\n", err);

  exit(1);
}

void ovm_call(OVMSTATE *ovm, OVMPTR bytecode_ptr, OVMUINT num_args)
{
  OVMPTR return_ptr = ovm->bytecode_ptr;
  OVMPTR frame_ptr = ovm->frame_ptr;

  ovm->bytecode_ptr = bytecode_ptr;
  ovm->frame_ptr = ovmstack_ptr(&ovm->stack) - num_args;

  OVMPTR this = ovmstack_top(&ovm->stack, num_args + 1).ptr_val;

  ovmstack_push(&ovm->stack, ovmstack_obj_of_uint(num_args));
  ovmstack_push(&ovm->stack, ovmstack_obj_of_ptr(return_ptr));
  ovmstack_push(&ovm->stack, ovmstack_obj_of_ptr(frame_ptr));
  ovmstack_push(&ovm->stack, ovmstack_obj_of_ptr(ovm->this));

  ovm->this = this;
}

void ovm_return(OVMSTATE *ovm)
{
  ovm->this = ovmstack_pop(&ovm->stack).ptr_val;
  ovm->frame_ptr = ovmstack_pop(&ovm->stack).ptr_val;
  ovm->bytecode_ptr = ovmstack_pop(&ovm->stack).ptr_val;

  OVMUINT num_args = ovmstack_pop(&ovm->stack).uint_val;

  for (int i = 0; i < num_args; i++)
  {
    ovmstack_pop(&ovm->stack);
  }
}

void ovm_exit(OVMSTATE *ovm, OVMUINT exit_code)
{
  printf("OVM halted with exit code %u.\n", exit_code);

  exit(exit_code);
}
