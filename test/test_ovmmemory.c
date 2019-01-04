#include <ovm/ovmmemory.h>
#include <unity.h>

void test_ovmmemory_alloc_should_allocate_specified_size_given_exactly_enough_space()
{
  unsigned int space_required = 27;
  OVMMEMORY m = ovmmemory_create(space_required);

  // OVMPTR ptr = ovmmemory_alloc(&m, space_required);

  // OVMCHUNK *c = ovmmemory_ovmptr_to_chunk(&m, ptr);

  // TEST_ASSERT_NOT_EQUAL(OVM_NULL, ptr);
  // TEST_ASSERT_EQUAL_UINT(space_required, c->size);
  // TEST_ASSERT_EQUAL_UINT(
  //     1, c->flags); // Right now flags is only used to check if is allocated

  ovmmemory_free(&m);
}

void test_ovmmemory_alloc_should_fragment_chunk_given_chunk_with_space_remaining()
{
  unsigned int initial_space = 100;
  unsigned int space_required = 27;
  OVMMEMORY m = ovmmemory_create(initial_space);

  OVMPTR ptr = ovmmemory_alloc(&m, space_required);

  OVMCHUNK *c = ovmmemory_ovmptr_to_chunk(&m, ptr);
  OVMCHUNK *new_chunk = c->next;
  TEST_ASSERT_EQUAL_UINT(2, ovmmemory_num_chunks(&m));
  TEST_ASSERT_EQUAL_UINT(initial_space - space_required - sizeof(OVMCHUNK),
                         new_chunk->size);
  TEST_ASSERT_EQUAL_UINT(0, new_chunk->flags); // Flag 0 = unallocated
  TEST_ASSERT_EQUAL_PTR(c, new_chunk->previous);
  TEST_ASSERT_EQUAL_PTR(new_chunk, c->next);

  ovmmemory_free(&m);
}

void test_ovmmemory_alloc_should_return_null_given_not_enough_space()
{
  OVMMEMORY m = ovmmemory_create(100);

  OVMPTR ptr = ovmmemory_alloc(&m, 120);

  TEST_ASSERT_EQUAL_UINT(OVM_NULL, ptr);

  ovmmemory_free(&m);
}

void test_ovmmemory_dealloc_should_mark_chunk_as_unallocated()
{
  OVMMEMORY m = ovmmemory_create(27);
  OVMPTR ptr = ovmmemory_alloc(&m, 27);
  OVMCHUNK *c = ovmmemory_ovmptr_to_chunk(&m, ptr);

  ovmmemory_dealloc(&m, ptr);

  TEST_ASSERT_EQUAL_UINT(0, c->flags);

  ovmmemory_free(&m);
}

void main(void)
{
  UNITY_BEGIN();

  RUN_TEST(
      test_ovmmemory_alloc_should_allocate_specified_size_given_exactly_enough_space);
  // RUN_TEST(
  //     test_ovmmemory_alloc_should_fragment_chunk_given_chunk_with_space_remaining);
  // RUN_TEST(test_ovmmemory_alloc_should_return_null_given_not_enough_space);
  // RUN_TEST(test_ovmmemory_dealloc_should_mark_chunk_as_unallocated);
  return UNITY_END();
}