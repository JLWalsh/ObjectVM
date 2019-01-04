#ifndef OMEMORY_H
#define OMEMORY_H

#include "otypes.h"
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

typedef struct OMEMORY_T {
  char *start;
  uint64_t size;
} OMEMORY;

OMEMORY omemory_create(uint64_t start_size);

void omemory_free(OMEMORY *o);

OVMPTR omemory_alloc(OMEMORY *o, uint64_t size);

void omemory_dealloc(OMEMORY *o, OVMPTR value);

void *omemory_at(OMEMORY *o, OVMPTR value);

OVMPTR omemory_ptr_of_chunk(OMEMORY *o, OVMCHUNK *chunk);

OVMCHUNK *omemory_ovmptr_to_chunk(OMEMORY *o, OVMPTR ptr);

OVMUINT omemory_num_chunks(OMEMORY *o);

void omemory_dump(OMEMORY *o);

#endif /* OMEMORY_H */
