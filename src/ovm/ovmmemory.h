#ifndef OVMMEMORY_H
#define OVMMEMORY_H

#include <stdint.h>
#include "ovmtypes.h"

typedef struct OVMCHUNK_T
{
    struct OVMCHUNK_T *previous;
    struct OVMCHUNK_T *next;
    uint64_t size;
    uint8_t flags;
} OVMCHUNK;

typedef struct OVMMEMORY_T
{
    OVMCHUNK *start;
    uint64_t size;
} OVMMEMORY;

OVMMEMORY ovmmemory_create(uint64_t initial_size);

OVMPTR ovmmemory_allocate(OVMMEMORY *m, uint64_t size);

void ovmmemory_free(OVMMEMORY *m, OVMPTR ptr);

#endif /* OVMMEMORY_H */
