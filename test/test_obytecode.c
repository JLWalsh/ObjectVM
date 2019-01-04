#include <ovm/obytecode.h>
#include <ovm/ostate.h>
#include <unity.h>

char bytecode[] = {1, 2, 3, 4};
OSTATE ovm;

void set_up() {
  ovm.bytecode = &bytecode;
  ovm.bytecode_ptr = 0;
  ovm.bytecode_length = sizeof(bytecode);
}

void test_obytecode_read_should_advance_bytecode_ptr_by_read_size() {
  size_t read_size = 2;
  OVM_UINT initial_bytecode_ptr = 1;
  ovm.bytecode_ptr = initial_bytecode_ptr;

  obytecode_read(&ovm, read_size);

  TEST_ASSERT_EQUAL(initial_bytecode_ptr + read_size, ovm.bytecode_ptr);
}

void test_obytecode_read_should_return_pointer_to_current_bytecode() {
  ovm.bytecode_ptr = 2;

  void *ptr = obytecode_read(&ovm, 1);

  TEST_ASSERT_EQUAL_PTR(&bytecode[2], ptr);
}

void test_obytecode_read_op_should_read_op() {
  char op_bytecode[] = {0, 2, 3};
  ovm.bytecode_ptr = 1;
  ovm.bytecode = &op_bytecode;

  OVM_OP op = obytecode_read_op(&ovm);

  TEST_ASSERT_EQUAL_UINT(2, op);
}

void test_obytecode_read_uint_should_read_uint() {
  char uint_bytecode[] = {4, 0, 6};
  ovm.bytecode_ptr = 1;
  ovm.bytecode = &uint_bytecode;

  OVM_UINT uint = obytecode_read_uint(&ovm);

  TEST_ASSERT_EQUAL_UINT(6, uint);
}

void main(void) {
  set_up();
  UNITY_BEGIN();

  RUN_TEST(test_obytecode_read_should_advance_bytecode_ptr_by_read_size);
  RUN_TEST(test_obytecode_read_should_return_pointer_to_current_bytecode);
  RUN_TEST(test_obytecode_read_op_should_read_op);
  RUN_TEST(test_obytecode_read_uint_should_read_uint);

  return UNITY_END();
}