#ifndef oexecutor_INT_H
#define oexecutor_INT_H

#include "oexecutor.h"
#include "ovmstate.h"

void oexecutor_ui_push(OVMSTATE *ovm);

void oexecutor_ui_print(OVMSTATE *ovm);

void oexecutor_ui_global_load(OVMSTATE *ovm);

void oexecutor_ui_global_store(OVMSTATE *ovm);

#endif /* oexecutor_INT_H */
