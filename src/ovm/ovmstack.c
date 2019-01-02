#include "ovmstack.h"
#include <malloc.h>

OVMSTACK ovmstack_create(uint16_t initial_size)
{
    OVMSTACK s;
    s.size = 0;
    s.max_size = initial_size;
    s.objects = (OVMSTACK_OBJECT *)malloc(sizeof(OVMSTACK_OBJECT) * initial_size);

    return s;
}

void ovmstack_free(OVMSTACK *s)
{
    free(s->objects);
    s->objects = NULL;
}

void ovmstack_push(OVMSTACK *s, OVMSTACK_OBJECT o)
{
    s->objects[s->size++] = o;
}

OVMSTACK_OBJECT ovmstack_pop(OVMSTACK *s) { return s->objects[--s->size]; }

OVMPTR ovmstack_ptr(OVMSTACK *s) { return (OVMPTR)s->size; }
