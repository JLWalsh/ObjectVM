#include "ovmmemory.h"
#include "ovmflag.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

OVMMEMORY ovmmemory_create(uint64_t start_size)
{
  size_t chunk_headers_size = sizeof(OVMCHUNK);
  size_t full_size = chunk_headers_size + start_size;

  char *ovmmemory_start = (char *)malloc(full_size + 1);
  OVMCHUNK *first_chunk =
      (OVMCHUNK *)(ovmmemory_start + 1); // First byte is reserved for VM_NULL

  first_chunk->previous = NULL;
  first_chunk->next = NULL;
  first_chunk->size = start_size;
  first_chunk->flags = 0;

  OVMMEMORY heap;
  heap.size = start_size;
  heap.start = (char *)first_chunk;

  return heap;
}

void ovmmemory_free(OVMMEMORY *o)
{
  free(o->start - 1); // First byte is reserved for VM_NULL
}

OVMPTR ovmmemory_alloc(OVMMEMORY *o, uint64_t size)
{
  OVMCHUNK *current = (OVMCHUNK *)o->start;

  while (current != NULL)
  {
    bool is_allocated = OVMFLAG_READ(current->flags, OVMCHUNK_FLAGS_ALLOCATED);
    bool is_readonly = OVMFLAG_READ(current->flags, OVMCHUNK_FLAGS_READONLY);

    if (current->size >= size && !is_allocated && !is_readonly)
    {
      OVMPTR pointer = ovmmemory_ptr_of_chunk(o, current);
      current->flags = OVMFLAG_ENABLE(current->flags, OVMCHUNK_FLAGS_ALLOCATED);

      if (current->size > size + sizeof(OVMCHUNK))
      {
        OVMCHUNK *data_end =
            (OVMCHUNK *)((char *)current + sizeof(OVMCHUNK) + size);

        if (current->next != NULL)
        {
          current->next->previous = data_end;
        }

        data_end->next = current->next;
        data_end->previous = current;
        current->next = data_end;

        data_end->flags = 0;
        data_end->size = current->size - sizeof(OVMCHUNK) - size;
        current->size = size;
      }

      return pointer;
    }

    current = current->next;
  }

  return OVM_NULL;
}

void ovmmemory_dealloc(OVMMEMORY *o, OVMPTR value)
{
  OVMCHUNK *chunk = ovmmemory_ovmptr_to_chunk(o, value);

  chunk->flags = OVMFLAG_DISABLE(chunk->flags, OVMCHUNK_FLAGS_ALLOCATED);
}

void *ovmmemory_at(OVMMEMORY *o, OVMPTR value)
{
  char *chunk_start = &o->start[value];
  chunk_start += sizeof(OVMCHUNK);

  return (void *)chunk_start;
}

OVMPTR ovmmemory_ptr_of_chunk(OVMMEMORY *o, OVMCHUNK *chunk)
{
  OVMPTR offset_from_start = (char *)chunk - o->start;

  return offset_from_start;
}

OVMCHUNK *ovmmemory_ovmptr_to_chunk(OVMMEMORY *o, OVMPTR ptr)
{
  char *chunk_ptr = o->start + ptr;

  return (OVMCHUNK *)chunk_ptr;
}

OVMUINT ovmmemory_num_chunks(OVMMEMORY *o)
{
  OVMUINT num_chunks = 0;
  OVMCHUNK *current = (OVMCHUNK *)o->start;

  while (current != NULL)
  {
    num_chunks++;
    current = current->next;
  }

  return num_chunks;
}

void ovmmemory_dump(OVMMEMORY *o)
{
  int chunk_counter = 0;

  OVMCHUNK *current = (OVMCHUNK *)o->start;
  for (;;)
  {
    if (current == NULL)
    {
      break;
    }

    printf("Chunk #%i (Flag: %i, size: %i):\n", chunk_counter, current->flags,
           current->size);

    char *data = (char *)current + sizeof(OVMCHUNK);
    for (int i = 0; i < current->size; i++)
    {
      printf("%i\n", data[i]);
    }
    chunk_counter++;
    current = current->next;
  }
}