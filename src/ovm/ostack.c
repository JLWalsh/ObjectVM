#include "ostack.h"
#include <malloc.h>

OSTACK ostack_create(uint16_t initial_size)
{
    OSTACK s;
    s.size = 0;
    s.max_size = initial_size;
    s.objects = (OSTACK_OBJECT *)malloc(sizeof(OSTACK_OBJECT) * initial_size);

    return s;
}

void ostack_free(OSTACK *s)
{
    free(s->objects);
    s->objects = NULL;
}

void ostack_push(OSTACK *s, OSTACK_OBJECT o) { s->objects[s->size++] = o; }

OSTACK_OBJECT ostack_pop(OSTACK *s) { return s->objects[--s->size]; }

OSTACK_OBJECT ostack_top(OSTACK *s, uint8_t offset)
{
    return s->objects[s->size - offset];
}

OSTACK_OBJECT ostack_at(OSTACK *s, OVM_PTR ptr) { return s->objects[ptr]; }

OVM_PTR ostack_ptr(OSTACK *s) { return (OVM_PTR)s->size; }

OSTACK_OBJECT ostack_obj_of_ptr(OVM_PTR ptr_val)
{
    OSTACK_OBJECT o;
    o.ptr_val = ptr_val;

    return o;
}

OSTACK_OBJECT ostack_obj_of_uint(OVM_UINT uint_val)
{
    OSTACK_OBJECT o;
    o.uint_val = uint_val;

    return o;
}
