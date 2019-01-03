#include "ovmexecutor.h"
#include "ovm.h"

void ovmexecutor_init_all()
{
    EXECUTORS[OP_INVOKE] = ovmexecutor_invoke;
    EXECUTORS[OP_INVOKE_SUPER] = ovmexecutor_invoke_super;
    EXECUTORS[OP_RETURN] = ovmexecutor_return;
    EXECUTORS[OP_UI_PUSH] = ovmexecutor_ui_push;
    EXECUTORS[OP_UI_PRINT] = ovmexecutor_ui_print;
    EXECUTORS[OP_HALT] = ovmexecutor_halt;
}

void ovmexecutor_return(OVMSTATE *ovm)
{
    ovm_return(ovm);
}

void ovmexecutor_halt(OVMSTATE *ovm)
{
    ovm_exit(ovm, 0);
}
