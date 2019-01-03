#include <ovm/ovmobject.h>
#include <unity.h>

OVMOBJECT gen_ovmobject_with(OVMOBJECT_FUNC_TABLE func_table)
{
  OVMOBJECT o;
  o.funcs = func_table;

  return o;
}

OVMOBJECT_FUNC_TABLE gen_ovmobject_func_table(OVMPTR *table, uint8_t size)
{
  OVMOBJECT_FUNC_TABLE func_table;
  func_table.func_ptrs = table;
  func_table.num_funcs = size;

  return func_table;
}

void test_ovmobject_should_resolve_existing_method()
{
  OVMPTR func_ptrs[] = {10, 30};
  OVMOBJECT_FUNC_TABLE func_table = gen_ovmobject_func_table(&func_ptrs, 2);
  OVMOBJECT o = gen_ovmobject_with(func_table);

  OVMPTR resolved_ptr = ovmobject_resolve_method(&o, 1);

  TEST_ASSERT_EQUAL_INT(30, resolved_ptr);
}

void test_ovmobject_should_resolve_base_method()
{
  OVMPTR child_func_ptrs[] = {34};
  OVMPTR base_func_ptrs[] = {27, 10};
  OVMOBJECT child =
      gen_ovmobject_with(gen_ovmobject_func_table(&child_func_ptrs, 1));
  OVMOBJECT base =
      gen_ovmobject_with(gen_ovmobject_func_table(&base_func_ptrs, 2));
  child.base = &base;

  OVMPTR resolved_ptr = ovmobject_base_resolve_method(&child, 0);

  TEST_ASSERT_EQUAL_INT(27, resolved_ptr);
}

void test_ovmobject_should_resolve_interface_method()
{
  OVMPTR vfunc_ptrs1[] = {1, 2, 3, 4};
  OVMPTR vfunc_ptrs2[] = {10, 20, 30};
  OVMOBJECT_FUNC_TABLE vfunc_table1 = gen_ovmobject_func_table(&vfunc_ptrs1, 4);
  OVMOBJECT_FUNC_TABLE vfunc_table2 = gen_ovmobject_func_table(&vfunc_ptrs2, 3);
  OVMOBJECT_FUNC_TABLE vfunc_tables[] = {vfunc_table1, vfunc_table2};
  OVMOBJECT o;
  o.vfuncs = &vfunc_tables;
  o.num_vfunc_tables = 2;

  OVMPTR resolved_ptr = ovmobject_interface_resolve_method(&o, 1, 2);

  TEST_ASSERT_EQUAL_INT(30, resolved_ptr);
}

void test_strict_ovmobject_resolve_should_return_null_given_non_existing_method()
{
  OVMOBJECT_FUNC_TABLE func_table = gen_ovmobject_func_table(NULL, 0);
  OVMOBJECT o = gen_ovmobject_with(func_table);

  OVMPTR resolved_ptr = ovmobject_resolve_method(&o, 12);

  TEST_ASSERT_EQUAL_INT(OVM_NULL, resolved_ptr);
}

void test_strict_ovmobject_should_resolve_base_return_null_given_no_base_object()
{
  OVMOBJECT o;
  o.base = NULL;

  OVMPTR resolved_ptr = ovmobject_base_resolve_method(&o, 0);

  TEST_ASSERT_EQUAL_INT(OVM_NULL, resolved_ptr);
}

void test_strict_ovmobject_resolve_interface_should_return_null_given_non_existing_interface()
{
  OVMPTR vfunc_ptrs1[] = {1, 2, 3, 4};
  OVMOBJECT_FUNC_TABLE vfunc_table = gen_ovmobject_func_table(&vfunc_ptrs1, 4);
  OVMOBJECT_FUNC_TABLE vfunc_tables[] = {vfunc_table};
  OVMOBJECT o;
  o.vfuncs = &vfunc_tables;
  o.num_vfunc_tables = 1;

  OVMPTR resolved_ptr = ovmobject_interface_resolve_method(&o, 1, 2);

  TEST_ASSERT_EQUAL_INT(OVM_NULL, resolved_ptr);
}

void test_strict_ovmobject_resolve_interface_should_return_null_given_non_existing_method()
{
  OVMPTR vfunc_ptrs1[] = {1, 2, 3, 4};
  OVMOBJECT_FUNC_TABLE vfunc_table = gen_ovmobject_func_table(&vfunc_ptrs1, 4);
  OVMOBJECT_FUNC_TABLE vfunc_tables[] = {vfunc_table};
  OVMOBJECT o;
  o.vfuncs = &vfunc_tables;
  o.num_vfunc_tables = 1;

  OVMPTR resolved_ptr = ovmobject_interface_resolve_method(&o, 0, 5);

  TEST_ASSERT_EQUAL_INT(OVM_NULL, resolved_ptr);
}

int main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_ovmobject_should_resolve_existing_method);
  RUN_TEST(test_ovmobject_should_resolve_base_method);
  RUN_TEST(test_ovmobject_should_resolve_interface_method);

#ifdef VM_STRICT_MODE
  RUN_TEST(
      test_strict_ovmobject_resolve_should_return_null_given_non_existing_method);
  RUN_TEST(
      test_strict_ovmobject_should_resolve_base_return_null_given_no_base_object);
  RUN_TEST(
      test_strict_ovmobject_resolve_interface_should_return_null_given_non_existing_interface);
  RUN_TEST(
      test_strict_ovmobject_resolve_interface_should_return_null_given_non_existing_method);
#endif

  return UNITY_END();
}