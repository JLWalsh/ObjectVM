#ifndef OVMMEMORY_H
#define OVMMEMORY_H

#include "ovmtypes.h"
#include <stdbool.h>
#include <stdlib.h>

typedef enum OVMCHUNK_FLAGS_T {
  OVMCHUNK_FLAGS_READONLY = 1 << 0,
  OVMCHUNK_FLAGS_ALLOCATED = 1 << 1
} OVMCHUNK_FLAGS;

typedef struct OVMCHUNK_T {
  struct OVMCHUNK_T *previous;
  struct OVMCHUNK_T *next;
  uint64_t size;
  uint8_t flags;
} OVMCHUNK;

typedef struct OVMMEMORY_T {
  char *start;
  uint64_t size;
} OVMMEMORY;

OVMMEMORY ovmmemory_create(uint64_t start_size);

void ovmmemory_free(OVMMEMORY *o);

OVMPTR ovmmemory_alloc(OVMMEMORY *o, uint64_t size);

void ovmmemory_dealloc(OVMMEMORY *o, OVMPTR value);

void *ovmmemory_at(OVMMEMORY *o, OVMPTR value);

OVMPTR ovmmemory_ptr_of_chunk(OVMMEMORY *o, OVMCHUNK *chunk);

OVMCHUNK *ovmmemory_ovmptr_to_chunk(OVMMEMORY *o, OVMPTR ptr);

OVMUINT ovmmemory_num_chunks(OVMMEMORY *o);

void ovmmemory_dump(OVMMEMORY *o);

#endif /* OVMMEMORY_H */
