#ifndef TEST_HEADER_
#define TEST_HEADER_

#include "../headers/s21_common.h"
#include "../s21_decimal.h"
#include "s21_test.h"

#endif

START_TEST(s21_negate_test1) {
  s21_decimal input = {123123, 123213, 0, 0};
  s21_decimal expected;
  copyNumber(&expected, &input);
  setSign(&expected, reverseBit(getSign(&input)));

  s21_decimal result = {0};
  s21_negate(input, &result);

  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

START_TEST(s21_negate_test2) {
  s21_decimal input = {12311243, 123213, 1241241241, 0};
  s21_decimal expected;
  copyNumber(&expected, &input);
  setSign(&expected, reverseBit(getSign(&input)));

  s21_decimal result = {0};
  s21_negate(input, &result);

  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

START_TEST(s21_negate_test3) {
  s21_decimal input = {12311243, 123213, 1241241241, 0};
  setScale(&input, 12);
  s21_decimal expected;
  copyNumber(&expected, &input);
  setSign(&expected, reverseBit(getSign(&input)));

  s21_decimal result = {0};
  s21_negate(input, &result);

  ASSERT_DECIMAL_EQ(result, expected)
}

START_TEST(s21_negate_test4) {
  s21_decimal input = {0, 0, 0, 0};
  s21_decimal expected;
  copyNumber(&expected, &input);
  setSign(&expected, reverseBit(getSign(&input)));

  s21_decimal result = {0};
  s21_negate(input, &result);

  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

START_TEST(s21_negate_test5) {
  s21_decimal input = {1, 0, 0, 0};
  s21_decimal expected;
  copyNumber(&expected, &input);
  setSign(&expected, reverseBit(getSign(&input)));

  s21_decimal result = {0};
  s21_negate(input, &result);

  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

Suite *

negate_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("negate");
  tc_core = tcase_create("core");

  tcase_add_test(tc_core, s21_negate_test1);
  tcase_add_test(tc_core, s21_negate_test2);
  tcase_add_test(tc_core, s21_negate_test3);
  tcase_add_test(tc_core, s21_negate_test4);
  tcase_add_test(tc_core, s21_negate_test5);

  suite_add_tcase(s, tc_core);
  return s;
}
