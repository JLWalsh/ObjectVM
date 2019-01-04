#include <ovm/oobject.h>
#include <unity.h>

OOBJECT gen_oobject_with(OOBJECT_FUNC_TABLE func_table)
{
  OOBJECT o;
  o.funcs = func_table;

  return o;
}

OOBJECT_FUNC_TABLE gen_oobject_func_table(OVM_PTR *table, uint8_t size)
{
  OOBJECT_FUNC_TABLE func_table;
  func_table.func_ptrs = table;
  func_table.num_funcs = size;

  return func_table;
}

void test_oobject_should_resolve_existing_method()
{
  OVM_PTR func_ptrs[] = {10, 30};
  OOBJECT_FUNC_TABLE func_table = gen_oobject_func_table(&func_ptrs, 2);
  OOBJECT o = gen_oobject_with(func_table);

  OVM_PTR resolved_ptr = oobject_resolve_method(&o, 1);

  TEST_ASSERT_EQUAL_INT(30, resolved_ptr);
}

void test_oobject_should_resolve_base_method()
{
  OVM_PTR child_func_ptrs[] = {34};
  OVM_PTR base_func_ptrs[] = {27, 10};
  OOBJECT child = gen_oobject_with(gen_oobject_func_table(&child_func_ptrs, 1));
  OOBJECT base = gen_oobject_with(gen_oobject_func_table(&base_func_ptrs, 2));
  child.base = &base;

  OVM_PTR resolved_ptr = oobject_base_resolve_method(&child, 0);

  TEST_ASSERT_EQUAL_INT(27, resolved_ptr);
}

void test_oobject_should_resolve_interface_method()
{
  OVM_PTR vfunc_ptrs1[] = {1, 2, 3, 4};
  OVM_PTR vfunc_ptrs2[] = {10, 20, 30};
  OOBJECT_FUNC_TABLE vfunc_table1 = gen_oobject_func_table(&vfunc_ptrs1, 4);
  OOBJECT_FUNC_TABLE vfunc_table2 = gen_oobject_func_table(&vfunc_ptrs2, 3);
  OOBJECT_FUNC_TABLE vfunc_tables[] = {vfunc_table1, vfunc_table2};
  OOBJECT o;
  o.vfuncs = &vfunc_tables;
  o.num_vfunc_tables = 2;

  OVM_PTR resolved_ptr = oobject_interface_resolve_method(&o, 1, 2);

  TEST_ASSERT_EQUAL_INT(30, resolved_ptr);
}

void test_strict_oobject_resolve_should_return_null_given_non_existing_method()
{
  OOBJECT_FUNC_TABLE func_table = gen_oobject_func_table(NULL, 0);
  OOBJECT o = gen_oobject_with(func_table);

  OVM_PTR resolved_ptr = oobject_resolve_method(&o, 12);

  TEST_ASSERT_EQUAL_INT(OVM_NULL, resolved_ptr);
}

void test_strict_oobject_should_resolve_base_return_null_given_no_base_object()
{
  OOBJECT o;
  o.base = NULL;

  OVM_PTR resolved_ptr = oobject_base_resolve_method(&o, 0);

  TEST_ASSERT_EQUAL_INT(OVM_NULL, resolved_ptr);
}

void test_strict_oobject_resolve_interface_should_return_null_given_non_existing_interface()
{
  OVM_PTR vfunc_ptrs1[] = {1, 2, 3, 4};
  OOBJECT_FUNC_TABLE vfunc_table = gen_oobject_func_table(&vfunc_ptrs1, 4);
  OOBJECT_FUNC_TABLE vfunc_tables[] = {vfunc_table};
  OOBJECT o;
  o.vfuncs = &vfunc_tables;
  o.num_vfunc_tables = 1;

  OVM_PTR resolved_ptr = oobject_interface_resolve_method(&o, 1, 2);

  TEST_ASSERT_EQUAL_INT(OVM_NULL, resolved_ptr);
}

void test_strict_oobject_resolve_interface_should_return_null_given_non_existing_method()
{
  OVM_PTR vfunc_ptrs1[] = {1, 2, 3, 4};
  OOBJECT_FUNC_TABLE vfunc_table = gen_oobject_func_table(&vfunc_ptrs1, 4);
  OOBJECT_FUNC_TABLE vfunc_tables[] = {vfunc_table};
  OOBJECT o;
  o.vfuncs = &vfunc_tables;
  o.num_vfunc_tables = 1;

  OVM_PTR resolved_ptr = oobject_interface_resolve_method(&o, 0, 5);

  TEST_ASSERT_EQUAL_INT(OVM_NULL, resolved_ptr);
}

int main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_oobject_should_resolve_existing_method);
  RUN_TEST(test_oobject_should_resolve_base_method);
  RUN_TEST(test_oobject_should_resolve_interface_method);

#ifdef VM_STRICT_MODE
  RUN_TEST(
      test_strict_oobject_resolve_should_return_null_given_non_existing_method);
  RUN_TEST(
      test_strict_oobject_should_resolve_base_return_null_given_no_base_object);
  RUN_TEST(
      test_strict_oobject_resolve_interface_should_return_null_given_non_existing_interface);
  RUN_TEST(
      test_strict_oobject_resolve_interface_should_return_null_given_non_existing_method);
#endif

  return UNITY_END();
}