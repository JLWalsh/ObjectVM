#include "ovmmemory.h"
#include <malloc.h>
#include <stdbool.h>

OVMMEMORY ovmmemory_create(uint64_t initial_size)
{
  OVMMEMORY m;
  m.size = initial_size;

  // Address 0 is reserved for OVM_NULL
  m.start = (char *)malloc(initial_size + sizeof(OVMCHUNK) + 1);

  m.chunk_start = (OVMCHUNK *)(m.start + 1);
  m.chunk_start->previous = NULL;
  m.chunk_start->next = NULL;
  m.chunk_start->size = initial_size;
  m.chunk_start->flags = 0;

  return m;
}

void ovmmemory_free(OVMMEMORY *m)
{
  if (m->start != NULL)
  {
    free(m->start);

    m->start = NULL;
    m->size = 0;
  }
}

OVMPTR ovmmemory_alloc(OVMMEMORY *m, uint64_t size)
{
  OVMCHUNK *current = m->chunk_start;

  while (current != NULL)
  {
    bool is_allocated = current->flags == 1;

    if (current->size >= size && !is_allocated)
    {
      bool can_fragment = current->size - (size + sizeof(OVMCHUNK)) > 0;

      if (can_fragment)
      {
        char *new_chunk_start = ovmmemory_chunk_data_ptr(current) + size;
        OVMCHUNK *new_chunk = (OVMCHUNK *)new_chunk_start;

        new_chunk->previous = current;
        new_chunk->next = current->next;
        if (current->next != NULL)
        {
          current->next->previous = new_chunk;
        }
        current->next = new_chunk;

        new_chunk->size = current->size - sizeof(OVMCHUNK) - size;
        new_chunk->flags = 0;
        current->size = size;
      }

      current->flags = 1;

      return ovmmemory_chunk_to_ovmptr(m, current);
    }

    current = current->next;
  }

  return OVM_NULL;
}

void ovmmemory_dealloc(OVMMEMORY *m, OVMPTR ptr)
{
  OVMCHUNK *c = ovmmemory_ovmptr_to_chunk(m, ptr);
  c->flags = 0;
}

char *ovmmemory_chunk_data_ptr(OVMCHUNK *c)
{
  return ((char *)c) + sizeof(OVMCHUNK);
}

OVMPTR ovmmemory_chunk_to_ovmptr(OVMMEMORY *m, OVMCHUNK *c)
{
  return (OVMPTR)((char *)c - m->start) + 1;
}

OVMCHUNK *ovmmemory_ovmptr_to_chunk(OVMMEMORY *m, OVMPTR ptr)
{
  return (OVMCHUNK *)(m->start + ptr - 1);
}

OVMUINT ovmmemory_num_chunks(OVMMEMORY *m)
{
  OVMUINT num_chunks = 0;

  OVMCHUNK *current = m->chunk_start;

  while (current != NULL)
  {
    num_chunks++;
    current = current->next;
  }

  return num_chunks;
}

void ovmmemory_dump(OVMMEMORY *m)
{
  OVMCHUNK *current = m->chunk_start;
  int chunkid = 0;
  while (current != NULL)
  {
    printf("Chunk #%i: size is %u, flag is %u. \n", chunkid, current->size,
           current->flags);
    chunkid++;
    current = current->next;
  }
}
