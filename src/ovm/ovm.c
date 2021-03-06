#include "ovm.h"
#include "obytecode.h"
#include "oexecutor.h"
#include "ostack.h"
#include <stdio.h>
#include <stdlib.h>

void ovm_init() { oexecutor_init_all(); }

OSTATE ovm_create(uint16_t stack_size, char *bytecode, uint64_t bytecode_length,
                  uint64_t initial_heap_size) {
  OSTATE ovm;
  ovm.num_objects = 0;
  ovm.objects = NULL;
  ovm.stack = ostack_create(stack_size);
  ovm.frame_ptr = 0;

  ovm.bytecode = bytecode;
  ovm.bytecode_length = bytecode_length;
  ovm.bytecode_ptr = 1; // 0 is reserved for OVM_NULL

  ovm.memory = omemory_create(initial_heap_size);

  return ovm;
}

void ovm_free(OSTATE *ovm) {
  ostack_free(&ovm->stack);
  omemory_free(&ovm->memory);
}

void ovm_run(OSTATE *ovm) {
  for (;;) {
    OVM_OP op = obytecode_read_op(ovm);

    EXECUTORS[op](ovm);
  }
}

void ovm_load_object(OSTATE *ovm, OOBJECT o) {
  ovm->num_objects++;
  ovm->objects = realloc(ovm->objects, sizeof(OOBJECT) * ovm->num_objects);
  ovm->objects[ovm->num_objects - 1] = o;
}

void ovm_throw(OSTATE *ovm, char *err) {
  printf("Exception encountered: %s\n", err);

  exit(1);
}

void ovm_call(OSTATE *ovm, OVM_PTR bytecode_ptr, OVM_UINT num_args,
              OVM_PTR obj_ref) {
  ostack_push(&ovm->stack, ostack_obj_of_ptr(obj_ref));

  ovm_call_static(ovm, bytecode_ptr,
                  num_args + 1); // Num_args + 1 because we push
                                 // the object reference as an
                                 // argument
}

void ovm_call_static(OSTATE *ovm, OVM_PTR bytecode_ptr, OVM_UINT num_args) {
  OVM_PTR return_ptr = ovm->bytecode_ptr;
  OVM_PTR frame_ptr = ovm->frame_ptr;

  ovm->bytecode_ptr = bytecode_ptr;
  ovm->frame_ptr = ostack_index(&ovm->stack);

  ostack_push(&ovm->stack, ostack_obj_of_uint(num_args));
  ostack_push(&ovm->stack, ostack_obj_of_ptr(return_ptr));
  ostack_push(&ovm->stack, ostack_obj_of_ptr(frame_ptr));
}

void ovm_return(OSTATE *ovm) {
  ostack_to_index(&ovm->stack, ovm->frame_ptr + 3);

  ovm->frame_ptr = ostack_pop(&ovm->stack).ptr_val;
  ovm->bytecode_ptr = ostack_pop(&ovm->stack).ptr_val;

  OVM_UINT num_args = ostack_pop(&ovm->stack).uint_val;

  for (int i = 0; i < num_args; i++) {
    ostack_pop(&ovm->stack);
  }
}

void ovm_exit(OSTATE *ovm, OVM_UINT exit_code) {
  printf("OVM halted with exit code %u.\n", exit_code);

  exit(exit_code);
}

OOBJECT *ovm_object_at(OSTATE *ovm, OVM_PTR obj_ptr) {
  void *obj_data_ptr = omemory_at(&ovm->memory, obj_ptr);
  OVM_UINT obj_id = oobject_data_get_id(obj_data_ptr);

  return &ovm->objects[obj_id];
}
