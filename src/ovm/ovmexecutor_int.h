#ifndef OVMEXECUTOR_INT_H
#define OVMEXECUTOR_INT_H

#include "ovmexecutor.h"
#include "ovmstate.h"

void ovmexecutor_ui_push(OVMSTATE *ovm);

void ovmexecutor_ui_print(OVMSTATE *ovm);

void ovmexecutor_ui_global_load(OVMSTATE *ovm);

void ovmexecutor_ui_global_store(OVMSTATE *ovm);

#endif /* OVMEXECUTOR_INT_H */
