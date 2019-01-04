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

void ovm_call(OSTATE *ovm, OVMPTR bytecode_ptr, OVMUINT num_args);

void ovm_return(OSTATE *ovm);

void ovm_exit(OSTATE *ovm, OVMUINT exit_code);

#endif /* OVM_H */
