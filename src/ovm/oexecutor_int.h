#ifndef OEXECUTOR_INT_H
#define OEXECUTOR_INT_H

#include "oexecutor.h"
#include "ostate.h"

void oexecutor_ui_push(OSTATE *ovm);

void oexecutor_ui_print(OSTATE *ovm);

void oexecutor_ui_global_load(OSTATE *ovm);

void oexecutor_ui_global_store(OSTATE *ovm);

#endif /* OEXECUTOR_INT_H */
