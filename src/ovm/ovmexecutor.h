#ifndef OVMEXECUTOR_H
#define OVMEXECUTOR_H

#include "ovmexecutor_invoke.h"
#include "ovmexecutor_int.h"
#include "ovmops.h"
#include "ovmstate.h"

typedef void (*EXECUTOR)(OVMSTATE *ovm);

EXECUTOR EXECUTORS[NUM_OF_OPS];

void ovmexecutor_init_all();

void ovmexecutor_return(OVMSTATE *ovm);

void ovmexecutor_halt(OVMSTATE *ovm);

void ovmexecutor_invoke(OVMSTATE *ovm);

void ovmexecutor_invoke_super(OVMSTATE *ovm);

#endif /* OVMEXECUTOR_H */
