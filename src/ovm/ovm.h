#ifndef OVM_H
#define OVM_H

#include "oobject.h"
#include "ostate.h"

void ovm_init();

OSTATE ovm_create(uint16_t stack_size, char *bytecode, uint64_t bytecode_length,
                  uint64_t initial_heap_size);

void ovm_free(OSTATE *ovm);

void ovm_run(OSTATE *ovm);

void ovm_load_object(OSTATE *ovm, OOBJECT o);

void ovm_throw(OSTATE *ovm, char *err);

void ovm_call(OSTATE *ovm, OVM_PTR bytecode_ptr, OVM_UINT num_args,
              OVM_PTR obj_ref);

void ovm_call_static(OSTATE *ovm, OVM_PTR bytecode_ptr, OVM_UINT num_args);

void ovm_return(OSTATE *ovm);

void ovm_exit(OSTATE *ovm, OVM_UINT exit_code);

OOBJECT *ovm_object_at(OSTATE *ovm, OVM_PTR obj_ptr);

#endif /* OVM_H */
