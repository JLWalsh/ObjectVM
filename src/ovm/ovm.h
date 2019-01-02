#ifndef OVM_H
#define OVM_H

#include "ovmobject.h"
#include "ovmstate.h"

void ovm_init();

OVMSTATE ovm_create(uint16_t stack_size);

void ovm_free(OVMSTATE *ovm);

void ovm_run(OVMSTATE *ovm, void *program);

void ovm_load_object(OVMSTATE *ovm, OVMOBJECT o);

void ovm_throw(OVMSTATE *ovm, char *err);

void ovm_call(OVMSTATE *ovm, OVMPTR bytecode_ptr, OVMUINT num_args);

void ovm_return(OVMSTATE *ovm);

#endif /* OVM_H */
