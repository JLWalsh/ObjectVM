#include <ovm/ovmflag.h>
#include <ovm/ovmmemory.h>
#include <stdbool.h>
#include <unity.h>

int number_of_chunks(OVMMEMORY memory) {
  OVMCHUNK *current = (OVMCHUNK *)memory.start;
  int num_chunks = 0;

  while (current != NULL) {
    num_chunks++;
    current = current->next;
  }

  return num_chunks;
}

void test_ovmmemory_alloc_should_create_new_chunk_out_of_remaining_memory() {
  OVMMEMORY memory = ovmmemory_create(120);

  ovmmemory_alloc(&memory, 60);
  TEST_ASSERT_EQUAL_INT(2, number_of_chunks(memory));

  ovmmemory_free(&memory);
}

void test_ovmmemory_alloc_should_create_chunk_with_specified_size() {
  OVMMEMORY memory = ovmmemory_create(120);

  OVMPTR ptr = ovmmemory_alloc(&memory, 60);

  OVMCHUNK *allocated_chunk = ovmmemory_ovmptr_to_chunk(&memory, ptr);
  TEST_ASSERT_EQUAL_UINT(60, allocated_chunk->size);
  TEST_ASSERT_TRUE(
      OVMFLAG_READ(allocated_chunk->flags, OVMCHUNK_FLAGS_ALLOCATED));

  ovmmemory_free(&memory);
}

void test_ovmmemory_alloc_should_not_split_chunks_when_not_enough_memory_for_new_chunk() {
  int first_chunk_size = 120;
  OVMMEMORY memory = ovmmemory_create(first_chunk_size);

  OVMPTR ptr = ovmmemory_alloc(&memory, first_chunk_size);

  TEST_ASSERT_EQUAL_INT(1, number_of_chunks(memory));
  TEST_ASSERT_EQUAL_UINT(first_chunk_size,
                         ovmmemory_ovmptr_to_chunk(&memory, ptr)->size);

  ovmmemory_free(&memory);
}

void test_ovmmemory_alloc_should_return_null_if_allocation_exceeds_memory_available() {
  int memory_available = 120;
  OVMMEMORY memory = ovmmemory_create(memory_available);

  OVMPTR ptr = ovmmemory_alloc(&memory, memory_available + 20);

  TEST_ASSERT_EQUAL_INT(OVM_NULL, ptr);

  ovmmemory_free(&memory);
}

void test_ovmmemory_dealloc_should_remove_allocated_flag() {
  OVMMEMORY memory = ovmmemory_create(120);
  OVMPTR allocated_ptr = ovmmemory_alloc(&memory, 5);
  OVMCHUNK *allocated_chunk = ovmmemory_ovmptr_to_chunk(&memory, allocated_ptr);

  ovmmemory_dealloc(&memory, allocated_ptr);
  bool is_allocated =
      OVMFLAG_READ(allocated_chunk->flags, OVMCHUNK_FLAGS_ALLOCATED);
  TEST_ASSERT_FALSE(is_allocated);

  ovmmemory_free(&memory);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_ovmmemory_alloc_should_create_chunk_with_specified_size);
  RUN_TEST(
      test_ovmmemory_alloc_should_not_split_chunks_when_not_enough_memory_for_new_chunk);
  RUN_TEST(
      test_ovmmemory_alloc_should_return_null_if_allocation_exceeds_memory_available);
  RUN_TEST(
      test_ovmmemory_alloc_should_create_new_chunk_out_of_remaining_memory);
  RUN_TEST(test_ovmmemory_dealloc_should_remove_allocated_flag);

  return UNITY_END();
}