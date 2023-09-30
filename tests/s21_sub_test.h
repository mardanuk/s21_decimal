#ifndef TEST_HEADER_
#define TEST_HEADER_

#include "../headers/s21_common.h"
#include "../s21_decimal.h"
#include "s21_test.h"

#endif

START_TEST(s21_sub_test1) {
  s21_decimal number_1 = {{55555, 0, 0, 0}};
  s21_decimal number_2 = {{66666, 0, 0, 262144}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{555483334, 0, 0, 262144}};
  int function_returned = s21_sub(number_1, number_2, &result);

  ck_assert_uint_eq(function_returned, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

START_TEST(s21_sub_test2) {
  s21_decimal number_1 = {{UINT32_MAX, 0, 0, 2147614720}};
  s21_decimal number_2 = {{23465246, 0, 0, 2147549184}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{4060314835, 0, 0, 2147614720}};
  int function_returned = s21_sub(number_1, number_2, &result);

  ck_assert_uint_eq(function_returned, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

START_TEST(s21_sub_test3) {
  s21_decimal number_1 = {{UINT32_MAX, 0, 0, 0}};
  s21_decimal number_2 = {{UINT32_MAX, 100, 0, 0}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0, 100, 0, 2147483648}};
  int function_returned = s21_sub(number_1, number_2, &result);

  ck_assert_uint_eq(function_returned, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

START_TEST(s21_sub_test4) {
  s21_decimal number_1 = {{UINT32_MAX, 4563654, 0, 2148139008}};
  s21_decimal number_2 = {{23465246, 364563, 0, 2148270080}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{4271501950, 456000936, 0, 2148270080}};
  int function_returned = s21_sub(number_1, number_2, &result);

  ck_assert_uint_eq(function_returned, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

START_TEST(s21_sub_test5) {
  s21_decimal number_1 = {{UINT32_MAX, 345634, 0, 2147876864}};
  s21_decimal number_2 = {{23465246, 45634, 0, 327680}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{234652459, 801975, 0, 2147876864}};
  int function_returned = s21_sub(number_1, number_2, &result);

  ck_assert_uint_eq(function_returned, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

START_TEST(s21_sub_test6) {
  s21_decimal number_1 = {{UINT32_MAX, 345634, 0, 393216}};
  s21_decimal number_2 = {{23465246, 45634, 0, 2147811328}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{234652459, 801975, 0, 393216}};
  int function_returned = s21_sub(number_1, number_2, &result);

  ck_assert_uint_eq(function_returned, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

START_TEST(s21_sub_test7) {
  s21_decimal number_1 = {{UINT32_MAX, UINT32_MAX, 2147483647, 1638400}};
  s21_decimal number_2 = {{UINT32_MAX, UINT32_MAX, 0, 983040}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{4153960755, 858993458, 785251635, 2149056512}};
  int function_returned = s21_sub(number_1, number_2, &result);

  ck_assert_uint_eq(function_returned, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

START_TEST(s21_sub_test8) {
  s21_decimal number_1 = {{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0}};
  s21_decimal number_2 = {{4294967294, UINT32_MAX, UINT32_MAX, 0}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{1, 0, 0, 0}};
  int function_returned = s21_sub(number_1, number_2, &result);

  ck_assert_uint_eq(function_returned, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

START_TEST(s21_sub_test9) {
  s21_decimal number_1 = {{UINT32_MAX, UINT32_MAX, UINT32_MAX, 1835008}};
  s21_decimal number_2 = {{4294967294, UINT32_MAX, UINT32_MAX, 0}};

  s21_decimal result = {{0}};
  s21_decimal expected = {{4294967286, UINT32_MAX, UINT32_MAX, 2147483648}};
  int function_returned = s21_sub(number_1, number_2, &result);

  ck_assert_uint_eq(function_returned, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

// 79228162514264337593543950335 - 0.54 = 79228162514264337593543950334
START_TEST(s21_sub_test10) {
  s21_decimal number_1 = {{UINT32_MAX, UINT32_MAX, UINT32_MAX}};
  s21_decimal number_2 = {{54, 0, 0, 0}};
  setSign(&number_2, 0);
  setScale(&number_2, 2);
  s21_decimal result = {{0}};
  s21_decimal expected = {{0xFFFFFFFE, UINT32_MAX, UINT32_MAX}};
  int function_returned = s21_sub(number_1, number_2, &result);

  ck_assert_uint_eq(function_returned, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

START_TEST(s21_sub_test11) {
  s21_decimal number_1 = {{0x88c7bcb6, 0x9bdf88, 0, 0}};
  setSign(&number_1, 1);
  setScale(&number_1, 2);
  s21_decimal number_2 = {{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0}};
  setSign(&number_2, 1);
  setScale(&number_2, 0);
  s21_decimal result = {{0}};
  s21_decimal expected = {{0xf4646712, 0xfffe70f6, 0xffffffff}};
  int function_returned = s21_sub(number_1, number_2, &result);

  ck_assert_uint_eq(function_returned, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

START_TEST(s21_sub_test12) {
  s21_decimal number_1 = {{UINT32_MAX, UINT32_MAX, UINT32_MAX, 2147483648}};
  s21_decimal number_2 = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0, 0, 0, 0}};
  int function_returned = s21_sub(number_1, number_2, &result);

  ck_assert_uint_eq(function_returned,
                    errorCodeArithmetic_tooSmallOrNegativeInfinity);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

Suite *sub_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("sub");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_sub_test1);
  tcase_add_test(tc_core, s21_sub_test2);
  tcase_add_test(tc_core, s21_sub_test3);
  tcase_add_test(tc_core, s21_sub_test4);
  tcase_add_test(tc_core, s21_sub_test5);
  tcase_add_test(tc_core, s21_sub_test6);
  tcase_add_test(tc_core, s21_sub_test7);
  tcase_add_test(tc_core, s21_sub_test8);
  tcase_add_test(tc_core, s21_sub_test9);
  tcase_add_test(tc_core, s21_sub_test10);
  tcase_add_test(tc_core, s21_sub_test11);
  tcase_add_test(tc_core, s21_sub_test12);
  suite_add_tcase(s, tc_core);
  return s;
}
