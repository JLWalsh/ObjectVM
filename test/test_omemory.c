#include <ovm/oflag.h>
#include <ovm/omemory.h>
#include <stdbool.h>
#include <unity.h>

int number_of_chunks(OMEMORY memory) {
  OVMCHUNK *current = (OVMCHUNK *)memory.start;
  int num_chunks = 0;

  while (current != NULL) {
    num_chunks++;
    current = current->next;
  }

  return num_chunks;
}

void test_omemory_alloc_should_create_new_chunk_out_of_remaining_memory() {
  OMEMORY memory = omemory_create(120);

  omemory_alloc(&memory, 60);
  TEST_ASSERT_EQUAL_INT(2, number_of_chunks(memory));

  omemory_free(&memory);
}

void test_omemory_alloc_should_create_chunk_with_specified_size() {
  OMEMORY memory = omemory_create(120);

  OVMPTR ptr = omemory_alloc(&memory, 60);

  OVMCHUNK *allocated_chunk = omemory_ovmptr_to_chunk(&memory, ptr);
  TEST_ASSERT_EQUAL_UINT(60, allocated_chunk->size);
  TEST_ASSERT_TRUE(
      OFLAG_READ(allocated_chunk->flags, OVMCHUNK_FLAGS_ALLOCATED));

  omemory_free(&memory);
}

void test_omemory_alloc_should_not_split_chunks_when_not_enough_memory_for_new_chunk() {
  int first_chunk_size = 120;
  OMEMORY memory = omemory_create(first_chunk_size);

  OVMPTR ptr = omemory_alloc(&memory, first_chunk_size);

  TEST_ASSERT_EQUAL_INT(1, number_of_chunks(memory));
  TEST_ASSERT_EQUAL_UINT(first_chunk_size,
                         omemory_ovmptr_to_chunk(&memory, ptr)->size);

  omemory_free(&memory);
}

void test_omemory_alloc_should_return_null_if_allocation_exceeds_memory_available() {
  int memory_available = 120;
  OMEMORY memory = omemory_create(memory_available);

  OVMPTR ptr = omemory_alloc(&memory, memory_available + 20);

  TEST_ASSERT_EQUAL_INT(OVM_NULL, ptr);

  omemory_free(&memory);
}

void test_omemory_dealloc_should_remove_allocated_flag() {
  OMEMORY memory = omemory_create(120);
  OVMPTR allocated_ptr = omemory_alloc(&memory, 5);
  OVMCHUNK *allocated_chunk = omemory_ovmptr_to_chunk(&memory, allocated_ptr);

  omemory_dealloc(&memory, allocated_ptr);
  bool is_allocated =
      OFLAG_READ(allocated_chunk->flags, OVMCHUNK_FLAGS_ALLOCATED);
  TEST_ASSERT_FALSE(is_allocated);

  omemory_free(&memory);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_omemory_alloc_should_create_chunk_with_specified_size);
  RUN_TEST(
      test_omemory_alloc_should_not_split_chunks_when_not_enough_memory_for_new_chunk);
  RUN_TEST(
      test_omemory_alloc_should_return_null_if_allocation_exceeds_memory_available);
  RUN_TEST(test_omemory_alloc_should_create_new_chunk_out_of_remaining_memory);
  RUN_TEST(test_omemory_dealloc_should_remove_allocated_flag);

  return UNITY_END();
}