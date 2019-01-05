#include <ovm/odictionary.h>
#include <unity.h>

void test_odictionary_initial_size_should_be_zero() {
  ODICTIONARY d = odictionary_create(10);

  uint8_t size = odictionary_size(&d);

  TEST_ASSERT_EQUAL_UINT(0, size);

  odictionary_free(&d);
}

void test_odictionary_size_should_increase_by_one_when_new_entry_is_set() {
  ODICTIONARY d = odictionary_create(10);
  ODICTIONARY_VALUE key = {.uint_val = 10};
  ODICTIONARY_VALUE value = {.uint_val = 27};
  odictionary_set(&d, key, value);

  uint8_t size = odictionary_size(&d);

  TEST_ASSERT_EQUAL_UINT(1, size);

  odictionary_free(&d);
}

void test_odictionary_size_should_be_zero_when_new_entry_is_unset() {
  ODICTIONARY d = odictionary_create(10);
  ODICTIONARY_VALUE key = {.uint_val = 10};
  ODICTIONARY_VALUE value = {.uint_val = 27};
  odictionary_set(&d, key, value);
  odictionary_unset(&d, key);

  uint8_t size = odictionary_size(&d);

  TEST_ASSERT_EQUAL_UINT(0, size);

  odictionary_free(&d);
}

void test_odictionary_lookup_should_lookup_correct_entry_for_key() {
  ODICTIONARY d = odictionary_create(3);
  ODICTIONARY_VALUE key = {.uint_val = 10};
  ODICTIONARY_VALUE value = {.uint_val = 27};
  odictionary_set(&d, key, value);
  ODICTIONARY_VALUE key2 = {.uint_val = 45};
  ODICTIONARY_VALUE value2 = {.uint_val = 32};
  odictionary_set(&d, key2, value2);

  ODICTIONARY_ENTRY *e1 = odictionary_lookup(&d, key);
  ODICTIONARY_ENTRY *e2 = odictionary_lookup(&d, key2);

  TEST_ASSERT_EQUAL_UINT(value.uint_val, e1->value.uint_val);
  TEST_ASSERT_EQUAL_UINT(value2.uint_val, e2->value.uint_val);

  odictionary_free(&d);
}

void test_odictionary_lookup_should_return_null_given_no_matching_key() {
  ODICTIONARY d = odictionary_create(3);
  ODICTIONARY_VALUE key = {.uint_val = 45};

  ODICTIONARY_ENTRY *e = odictionary_lookup(&d, key);

  TEST_ASSERT_NULL(e);

  odictionary_free(&d);
}

void test_odictionary_lookup_should_return_null_given_key_that_was_unset() {
  ODICTIONARY d = odictionary_create(3);
  ODICTIONARY_VALUE key = {.uint_val = 45};
  ODICTIONARY_VALUE value = {.uint_val = 32};
  odictionary_set(&d, key, value);
  odictionary_unset(&d, key);

  ODICTIONARY_ENTRY *e = odictionary_lookup(&d, key);

  TEST_ASSERT_NULL(e);

  odictionary_free(&d);
}

void test_odictionary_set_should_return_false_when_is_full() {
  ODICTIONARY d = odictionary_create(1);
  ODICTIONARY_VALUE key = {.uint_val = 10};
  ODICTIONARY_VALUE value = {.uint_val = 27};
  odictionary_set(&d, key, value);
  ODICTIONARY_VALUE key2 = {.uint_val = 45};
  ODICTIONARY_VALUE value2 = {.uint_val = 32};

  bool did_set = odictionary_set(&d, key2, value2);

  TEST_ASSERT_FALSE(did_set);

  odictionary_free(&d);
}

void test_odictionary_set_should_override_entry_if_exists() {
  ODICTIONARY d = odictionary_create(2);
  ODICTIONARY_VALUE key = {.uint_val = 10};
  ODICTIONARY_VALUE value = {.uint_val = 27};
  odictionary_set(&d, key, value);
  ODICTIONARY_VALUE second_value = {.uint_val = 32};

  odictionary_set(&d, key, second_value);

  ODICTIONARY_ENTRY *e = odictionary_lookup(&d, key);
  TEST_ASSERT_EQUAL_UINT(second_value.uint_val, e->value.uint_val);

  odictionary_free(&d);
}

void test_odictionary_set_should_add_entry_given_new_key() {
  ODICTIONARY d = odictionary_create(2);
  ODICTIONARY_VALUE key = {.uint_val = 10};
  ODICTIONARY_VALUE value = {.uint_val = 27};

  odictionary_set(&d, key, value);

  ODICTIONARY_ENTRY *e = odictionary_lookup(&d, key);
  TEST_ASSERT_EQUAL_UINT(value.uint_val, e->value.uint_val);

  odictionary_free(&d);
}

void test_odictionary_set_should_mark_entry_as_used() {
  ODICTIONARY d = odictionary_create(2);
  ODICTIONARY_VALUE key = {.uint_val = 10};
  ODICTIONARY_VALUE value = {.uint_val = 27};

  odictionary_set(&d, key, value);

  ODICTIONARY_ENTRY *e = odictionary_lookup(&d, key);
  TEST_ASSERT_TRUE(e->is_used);

  odictionary_free(&d);
}

void test_odictionary_unset_should_mark_entry_as_unused() {
  ODICTIONARY d = odictionary_create(1);
  ODICTIONARY_VALUE key = {.uint_val = 10};
  ODICTIONARY_VALUE value = {.uint_val = 27};
  odictionary_set(&d, key, value);
  ODICTIONARY_ENTRY *unset_entry = odictionary_lookup(&d, key);

  odictionary_unset(&d, key);

  TEST_ASSERT_FALSE(unset_entry->is_used);

  odictionary_free(&d);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_odictionary_initial_size_should_be_zero);
  RUN_TEST(test_odictionary_size_should_increase_by_one_when_new_entry_is_set);
  RUN_TEST(test_odictionary_size_should_be_zero_when_new_entry_is_unset);
  RUN_TEST(test_odictionary_lookup_should_lookup_correct_entry_for_key);
  RUN_TEST(test_odictionary_lookup_should_return_null_given_no_matching_key);
  RUN_TEST(test_odictionary_lookup_should_return_null_given_key_that_was_unset);
  RUN_TEST(test_odictionary_set_should_return_false_when_is_full);
  RUN_TEST(test_odictionary_set_should_override_entry_if_exists);
  RUN_TEST(test_odictionary_set_should_add_entry_given_new_key);
  RUN_TEST(test_odictionary_set_should_mark_entry_as_used);
  RUN_TEST(test_odictionary_unset_should_mark_entry_as_unused);

  return UNITY_END();
}