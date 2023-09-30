#ifndef TEST_HEADER_
#define TEST_HEADER_

#include "../headers/s21_common.h"
#include "../s21_decimal.h"
#include "s21_test.h"

#endif

START_TEST(s21_add_test1) {
  s21_decimal input1 = {{0b11111111111111111111111111111111,
                         0b11111111111111111111111111111111, 0, 0}};
  s21_decimal input2 = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0, 0, 1, 0}};
  int function_returned = s21_add(input1, input2, &result);
  ck_assert_uint_eq(function_returned, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}
END_TEST

START_TEST(s21_add_test2) {
  s21_decimal input1 = {{55555, 0, 0, 0}};
  s21_decimal input2 = {{66666, 0, 0, 262144}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{555616666, 0, 0, 262144}};
  int function_returned = s21_add(input1, input2, &result);

  ck_assert_uint_eq(function_returned, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}
END_TEST

START_TEST(s21_add_test3) {
  s21_decimal input1 = {{5555, 0, 0, 2147483648}};
  s21_decimal input2 = {{333333333, 0, 0, 327680}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{222166667, 0, 0, 2147811328}};
  int function_returned = s21_add(input1, input2, &result);

  ck_assert_uint_eq(function_returned, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}
END_TEST

START_TEST(s21_add_test4) {
  s21_decimal input1 = {{UINT_MAX, 0, 0, 327680}};
  s21_decimal input2 = {{UINT_MAX, 100, 0, 2148139008}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{4294867297, 99898, 0, 655360}};
  int function_returned = s21_add(input1, input2, &result);

  ck_assert_uint_eq(function_returned, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}
END_TEST

START_TEST(s21_add_test5) {
  s21_decimal input1 = {{UINT_MAX, 613566756, 0, 2147811328}};
  s21_decimal input2 = {{UINT_MAX, 214748364, 0, 2147745792}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{4294967285, 2761050406, 0, 2147811328}};
  int function_returned = s21_add(input1, input2, &result);

  ck_assert_uint_eq(function_returned, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}
END_TEST

START_TEST(s21_add_test6) {
  s21_decimal input1 = {{346456, 53345, 0, 2147942400}};
  s21_decimal input2 = {{567567, 3456567, 0, 262144}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{567220544, 3456513655, 0, 458752}};
  int function_returned = s21_add(input1, input2, &result);

  ck_assert_uint_eq(function_returned, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}
END_TEST

START_TEST(s21_add_test7) {
  s21_decimal input1 = {{UINT_MAX, UINT_MAX, 2147483647, 1638400}};
  s21_decimal input2 = {{UINT_MAX, UINT_MAX, 0, 2148466688}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{4153960755, 858993458, 785251635, 2149056512}};
  int function_returned = s21_add(input1, input2, &result);

  ck_assert_uint_eq(function_returned, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

START_TEST(s21_add_test8) {
  s21_decimal input1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 1638400}};
  s21_decimal input2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 2148466688}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{2701727008, 2450292888, UINT_MAX, 2148466688}};
  int function_returned = s21_add(input1, input2, &result);

  ck_assert_uint_eq(function_returned, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

// 79228162514264337593543950334 + 1.5 = INF
START_TEST(s21_add_test9) {
  s21_decimal input1 = {{4294967294, UINT_MAX, UINT_MAX, 0}};
  s21_decimal input2 = {{15, 0, 0, 65536}};

  s21_decimal result = {{0}};
  s21_decimal expected = {{0, 0, 0, 0}};
  int function_returned = s21_add(input1, input2, &result);

  ck_assert_uint_eq(function_returned, errorCodeArithmetic_tooLargeOrInfinity);
  ASSERT_DECIMAL_EQ(result, expected)
}
END_TEST

START_TEST(s21_add_test10) {
  s21_decimal input1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 2147483648}};
  s21_decimal input2 = {{1, 0, 0, 2147483648}};

  s21_decimal result = {{0}};
  s21_decimal expected = {{0, 0, 0, 0}};
  int function_returned = s21_add(input1, input2, &result);

  ck_assert_uint_eq(function_returned,
                    errorCodeArithmetic_tooSmallOrNegativeInfinity);
  ASSERT_DECIMAL_EQ(result, expected)
}
END_TEST
Suite *

add_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("add");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_add_test1);
  tcase_add_test(tc_core, s21_add_test2);
  tcase_add_test(tc_core, s21_add_test3);
  tcase_add_test(tc_core, s21_add_test4);
  tcase_add_test(tc_core, s21_add_test5);
  tcase_add_test(tc_core, s21_add_test6);
  tcase_add_test(tc_core, s21_add_test7);
  tcase_add_test(tc_core, s21_add_test8);
  tcase_add_test(tc_core, s21_add_test9);
  tcase_add_test(tc_core, s21_add_test10);
  suite_add_tcase(s, tc_core);
  return s;
}
