#ifndef OVMEXECUTOR_H
#define OVMEXECUTOR_H

#include "ovmexecutor_int.h"
#include "ovmops.h"
#include "ovmstate.h"

typedef void (*EXECUTOR)(OVMSTATE *ovm);

EXECUTOR EXECUTORS[NUM_OF_OPS];

void ovmexecutor_init_all();

void ovmexecutor_returnvoid(OVMSTATE *ovm);

void ovmexecutor_halt(OVMSTATE *ovm);

void ovmexecutor_invoke(OVMSTATE *ovm);

void ovmexecutor_invoke_super(OVMSTATE *ovm);

void ovmexecutor_local_load(OVMSTATE *ovm);

void ovmexecutor_new(OVMSTATE *ovm);

void ovmexecutor_dup(OVMSTATE *ovm);

#endif /* OVMEXECUTOR_H */
