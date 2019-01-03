#ifndef OVMEXECUTOR_H
#define OVMEXECUTOR_H

#include "ovmexecutor_invoke.h"
#include "ovmexecutor_int.h"
#include "ovmops.h"
#include "ovmstate.h"

typedef void (*EXECUTOR)(OVMSTATE *ovm);

static EXECUTOR EXECUTORS[NUM_OF_OPS];

void ovmexecutor_init_all()
{
    EXECUTORS[OP_INVOKE] = ovmexecutor_invoke;
    EXECUTORS[OP_INVOKE_SUPER] = ovmexecutor_invoke_super;
    EXECUTORS[OP_RETURN] = ovmexecutor_return;
    EXECUTORS[OP_UI_PUSH] = ovmexecutor_ui_push;
    EXECUTORS[OP_UI_PRINT] = ovmexecutor_ui_print;
}

void ovmexecutor_return(OVMSTATE *ovm);

void ovmexecutor_halt(OVMSTATE *ovm);

#endif /* OVMEXECUTOR_H */
