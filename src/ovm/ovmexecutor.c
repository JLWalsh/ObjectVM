#include "ovmexecutor.h"
#include "ovm.h"

void ovmexecutor_return(OVMSTATE *ovm)
{
    ovm_return(ovm);
}

void ovmexecutor_halt(OVMSTATE *ovm)
{
    ovm_exit(ovm, 0);
}
