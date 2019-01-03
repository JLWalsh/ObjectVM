#include "ovmexecutor_int.h"
#include "ovmbytecode.h"
#include <stdio.h>

void ovmexecutor_ui_push(OVMSTATE *ovm)
{
    OVMUINT uint = ovmbytecode_read_uint(ovm);

    ovmstack_push(&ovm->stack, ovmstack_obj_of_uint(uint));
}

void ovmexecutor_ui_print(OVMSTATE *ovm)
{
    OVMUINT uint = ovmstack_pop(ovm).uint_val;
    printf("%u", uint);
}
