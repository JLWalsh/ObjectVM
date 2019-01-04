#ifndef OVMMEMORY_H
#define OVMMEMORY_H

#include "ovmtypes.h"
#include <stdint.h>

typedef struct OVMCHUNK_T {
  struct OVMCHUNK_T *previous;
  struct OVMCHUNK_T *next;
  uint64_t size;
  uint8_t flags;
} OVMCHUNK;

typedef struct OVMMEMORY_T {
  OVMCHUNK *start;
  uint64_t size;
} OVMMEMORY;

OVMMEMORY ovmmemory_create(uint64_t initial_size);

void ovmmemory_free(OVMMEMORY *m);

OVMPTR ovmmemory_alloc(OVMMEMORY *m, uint64_t size);

void ovmmemory_dealloc(OVMMEMORY *m, OVMPTR ptr);

char *ovmmemory_chunk_data_ptr(OVMCHUNK *c);

OVMPTR ovmmemory_chunk_to_ovmptr(OVMMEMORY *m, OVMCHUNK *c);

OVMCHUNK *ovmmemory_ovmptr_to_chunk(OVMMEMORY *m, OVMPTR ptr);

OVMUINT ovmmemory_num_chunks(OVMMEMORY *m);

void ovmmemory_dump(OVMMEMORY *m);

#endif /* OVMMEMORY_H */
