#include "ovm.h"
#include <stdlib.h>

OVMSTATE ovm_create()
{
    OVMSTATE ovm;
    ovm.num_objects = 0;
    ovm.objects = NULL;

    return ovm;
}

void ovm_load_object(OVMSTATE *ovm, OVMOBJECT o)
{
    ovm->num_objects++;
    ovm->objects = realloc(ovm->objects, sizeof(OVMOBJECT) * ovm->num_objects);
    ovm->objects[ovm->num_objects - 1] = o;
}

void ovm_throw(OVMSTATE *ovm, char *err)
{
    printf("Exception encountered: %s", err);

    exit(1);
}
