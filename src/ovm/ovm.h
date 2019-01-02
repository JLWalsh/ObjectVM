#ifndef OVM_H
#define OVM_H

#include "ovmobject.h"
#include "ovmstate.h"

OVMSTATE ovm_create();

void ovm_load_object(OVMSTATE *ovm, OVMOBJECT o);

void ovm_throw(OVMSTATE *ovm, char *err);

#endif /* OVM_H */
