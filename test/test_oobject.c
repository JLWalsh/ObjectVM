#include <ovm/oobject.h>
#include <unity.h>

OOBJECT_FUNC_TABLE gen_oobject_func_table(OVM_PTR *table, uint8_t size)
{
  OOBJECT_FUNC_TABLE func_table = {.func_ptrs = odictionary_create(size)};

  for (int i = 0; i < size; i++)
  {
    ofunc_table_register_method(&func_table, i, table[i]);
  }

  return func_table;
}

void test_oobject_should_resolve_virtual_method()
{
  OVM_PTR vfunc_ptrs1[] = {1, 2, 3, 4};
  OVM_PTR vfunc_ptrs2[] = {10, 20, 30};
  OOBJECT_FUNC_TABLE vfunc_table1 = gen_oobject_func_table(&vfunc_ptrs1, 4);
  OOBJECT_FUNC_TABLE vfunc_table2 = gen_oobject_func_table(&vfunc_ptrs2, 3);

  OOBJECT o;
  o.vfuncs = odictionary_create(2);
  oobject_register_interface(&o, 0, &vfunc_table1);
  oobject_register_interface(&o, 3, &vfunc_table2);

  OVM_PTR resolved_ptr = oobject_virtual_resolve_method(&o, 3, 2);

  TEST_ASSERT_EQUAL_INT(30, resolved_ptr);

  odictionary_free(&o.vfuncs);
  odictionary_free(&vfunc_table1.func_ptrs);
  odictionary_free(&vfunc_table2.func_ptrs);
}

void test_strict_oobject_resolve_virtual_should_return_null_given_non_existing_interface()
{
  OOBJECT o;
  o.vfuncs = odictionary_create(1);

  OVM_PTR resolved_ptr = oobject_virtual_resolve_method(&o, 1, 2);

  TEST_ASSERT_EQUAL_INT(OVM_NULL, resolved_ptr);

  odictionary_free(&o.vfuncs);
}

void test_strict_oobject_resolve_virtual_should_return_null_given_non_existing_method()
{
  OVM_PTR vfunc_ptrs[] = {1, 2, 3, 4};
  OOBJECT_FUNC_TABLE vfunc_table = gen_oobject_func_table(&vfunc_ptrs, 4);
  OOBJECT o;
  o.vfuncs = odictionary_create(1);
  oobject_register_interface(&o, 10, &vfunc_table);

  OVM_PTR resolved_ptr = oobject_virtual_resolve_method(&o, 10, 5);

  TEST_ASSERT_EQUAL_INT(OVM_NULL, resolved_ptr);

  odictionary_free(&o.vfuncs);
  odictionary_free(&vfunc_table.func_ptrs);
}

int main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_oobject_should_resolve_virtual_method);

#ifdef VM_STRICT_MODE
  RUN_TEST(
      test_strict_oobject_resolve_virtual_should_return_null_given_non_existing_interface);
  RUN_TEST(
      test_strict_oobject_resolve_virtual_should_return_null_given_non_existing_method);
#endif

  return UNITY_END();
}