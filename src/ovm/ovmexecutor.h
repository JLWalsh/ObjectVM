#ifndef OVMEXECUTOR_H
#define OVMEXECUTOR_H

#include "ovminvoke.h"
#include "ovmops.h"
#include "ovmstate.h"

typedef void (*EXECUTOR)(OVMSTATE *ovm);

static EXECUTOR EXECUTORS[NUM_OF_OPS];

void ovmexecutor_init_all()
{
    EXECUTORS[OP_INVOKE] = ovminvoke;
    EXECUTORS[OP_INVOKE_SUPER] = ovminvoke_super;
}

#endif /* OVMEXECUTOR_H */
