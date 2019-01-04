#ifndef oexecutor_H
#define oexecutor_H

#include "oexecutor_int.h"
#include "ovmops.h"
#include "ovmstate.h"

typedef void (*EXECUTOR)(OVMSTATE *ovm);

EXECUTOR EXECUTORS[NUM_OF_OPS];

void oexecutor_init_all();

void oexecutor_returnvoid(OVMSTATE *ovm);

void oexecutor_halt(OVMSTATE *ovm);

void oexecutor_invoke(OVMSTATE *ovm);

void oexecutor_invoke_super(OVMSTATE *ovm);

void oexecutor_local_load(OVMSTATE *ovm);

void oexecutor_new(OVMSTATE *ovm);

void oexecutor_dup(OVMSTATE *ovm);

#endif /* oexecutor_H */
