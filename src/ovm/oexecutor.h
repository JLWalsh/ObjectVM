#ifndef OEXECUTOR_H
#define OEXECUTOR_H

#include "oexecutor_int.h"
#include "oops.h"
#include "ostate.h"

typedef void (*EXECUTOR)(OSTATE *ovm);

EXECUTOR EXECUTORS[NUM_OF_OPS];

void oexecutor_init_all();

void oexecutor_return_void(OSTATE *ovm);

void oexecutor_halt(OSTATE *ovm);

void oexecutor_invoke(OSTATE *ovm);

void oexecutor_invoke_virtual(OSTATE *ovm);

void oexecutor_invoke_static(OSTATE *ovm);

void oexecutor_local_load(OSTATE *ovm);

void oexecutor_new(OSTATE *ovm);

void oexecutor_dup(OSTATE *ovm);

#endif /* OEXECUTOR_H */
