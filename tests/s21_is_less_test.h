#ifndef TEST_HEADER_
#define TEST_HEADER_

#include "../headers/s21_common.h"
#include "../s21_decimal.h"
#include "s21_test.h"

#endif

START_TEST(s21_is_less_test1) {
  s21_decimal number1 = {{0b11111111111111111111111111111111,
                          0b11111111111111111111111111111111, 0, 0}};
  s21_decimal number2 = {{1, 0, 0, 0}};

  ck_assert_uint_eq(s21_is_less(number1, number2), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number1, number1), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number2, number2), returnValueComparison_false);
}

END_TEST

START_TEST(s21_is_less_test2) {
  s21_decimal number1 = {{1, 1, 1, 0}};
  s21_decimal number2 = {{1, 1, 1, 0}};

  ck_assert_uint_eq(s21_is_less(number1, number2), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number1, number1), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number2, number2), returnValueComparison_false);
}

END_TEST

START_TEST(s21_is_less_test3) {
  s21_decimal number1 = {{0, 1, 1, 0}};
  s21_decimal number2 = {{1, 1, 1, 0}};

  ck_assert_uint_eq(s21_is_less(number1, number2), returnValueComparison_true);
  ck_assert_uint_eq(s21_is_less(number1, number1), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number2, number2), returnValueComparison_false);
}

END_TEST

START_TEST(s21_is_less_test4) {
  s21_decimal number1 = {{1, 1, 1, 0}};
  s21_decimal number2 = {{0, 1, 1, 0}};

  ck_assert_uint_eq(s21_is_less(number1, number2), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number1, number1), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number2, number2), returnValueComparison_false);
}

END_TEST

START_TEST(s21_is_less_test5) {
  s21_decimal number1 = {{1, 1, 1, 0}};
  s21_decimal number2 = {{1, 1, 1, 0}};
  setScale(&number1, 28);

  ck_assert_uint_eq(s21_is_less(number1, number2), returnValueComparison_true);
  ck_assert_uint_eq(s21_is_less(number1, number1), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number2, number2), returnValueComparison_false);
}

END_TEST

START_TEST(s21_is_less_test6) {
  s21_decimal number1 = {{1, 1, 1, 0}};
  s21_decimal number2 = {{1, 1, 1, 0}};
  setScale(&number1, 29);

  ck_assert_uint_eq(s21_is_less(number1, number2), returnValueComparison_true);
  ck_assert_uint_eq(s21_is_less(number1, number1), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number2, number2), returnValueComparison_false);
}

END_TEST

START_TEST(s21_is_less_test7) {
  s21_decimal number1 = {{1, 1, 1, 0}};
  s21_decimal number2 = {{1, 1, 1, 0}};
  setSign(&number1, 1);

  ck_assert_uint_eq(s21_is_less(number1, number2), returnValueComparison_true);
  ck_assert_uint_eq(s21_is_less(number1, number1), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number2, number2), returnValueComparison_false);
}

END_TEST

START_TEST(s21_is_less_test8) {
  s21_decimal number1 = {{1, 1, 1, 0}};
  s21_decimal number2 = {{1, 1, 1, 0}};
  setSign(&number2, 1);

  ck_assert_uint_eq(s21_is_less(number1, number2), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number1, number1), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number2, number2), returnValueComparison_false);
}

END_TEST

START_TEST(s21_is_less_test9) {
  s21_decimal number1 = {{1, 1, 1, 0}};
  s21_decimal number2 = {{1, 1, 1, 0}};
  setSign(&number1, 1);
  setSign(&number2, 1);

  ck_assert_uint_eq(s21_is_less(number1, number2), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number1, number1), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number2, number2), returnValueComparison_false);
}

END_TEST

START_TEST(s21_is_less_test10) {
  s21_decimal number1 = {{1, 1, 1, 0}};
  s21_decimal number2 = {{1, 1, 1, 0}};
  setSign(&number1, 1);
  setScale(&number1, 28);

  ck_assert_uint_eq(s21_is_less(number1, number2), returnValueComparison_true);
  ck_assert_uint_eq(s21_is_less(number1, number1), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number2, number2), returnValueComparison_false);
}

END_TEST

START_TEST(s21_is_less_test11) {
  s21_decimal number1 = {{1, 1, 1, 0}};
  s21_decimal number2 = {{1, 1, 1, 0}};
  setSign(&number1, 1);
  setScale(&number1, 29);

  ck_assert_uint_eq(s21_is_less(number1, number2), returnValueComparison_true);
  ck_assert_uint_eq(s21_is_less(number1, number1), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number2, number2), returnValueComparison_false);
}

END_TEST

START_TEST(s21_is_less_test12) {
  s21_decimal number1 = {{1, 1, 1, 0}};
  s21_decimal number2 = {{1, 1, 1, 0}};
  setSign(&number2, 1);
  setScale(&number1, 28);

  ck_assert_uint_eq(s21_is_less(number1, number2), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number1, number1), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number2, number2), returnValueComparison_false);
}

END_TEST

START_TEST(s21_is_less_test13) {
  s21_decimal number1 = {{1, 1, 1, 0}};
  s21_decimal number2 = {{1, 1, 1, 0}};
  setSign(&number2, 1);
  setScale(&number1, 29);

  ck_assert_uint_eq(s21_is_less(number1, number2), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number1, number1), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number2, number2), returnValueComparison_false);
}

END_TEST

START_TEST(s21_is_less_test14) {
  s21_decimal number1 = {{1, 1, 1, 0}};
  s21_decimal number2 = {{1, 1, 1, 0}};
  setSign(&number1, 1);
  setSign(&number2, 1);
  setScale(&number1, 28);

  ck_assert_uint_eq(s21_is_less(number1, number2), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number1, number1), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number2, number2), returnValueComparison_false);
}

END_TEST

START_TEST(s21_is_less_test15) {
  s21_decimal number1 = {{1, 1, 1, 0}};
  s21_decimal number2 = {{1, 1, 1, 0}};
  setSign(&number2, 1);
  setSign(&number1, 1);
  setScale(&number1, 29);

  ck_assert_uint_eq(s21_is_less(number1, number2), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number1, number1), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number2, number2), returnValueComparison_false);
}

END_TEST

START_TEST(s21_is_less_test16) {
  s21_decimal number1 = {{1, 1, 1, 0}};
  s21_decimal number2 = {{1, 1, 1, 0}};
  setSign(&number1, 1);
  setScale(&number2, 28);

  ck_assert_uint_eq(s21_is_less(number1, number2), returnValueComparison_true);
  ck_assert_uint_eq(s21_is_less(number1, number1), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number2, number2), returnValueComparison_false);
}

END_TEST

START_TEST(s21_is_less_test17) {
  s21_decimal number1 = {{1, 1, 1, 0}};
  s21_decimal number2 = {{1, 1, 1, 0}};
  setSign(&number1, 1);
  setScale(&number2, 29);

  ck_assert_uint_eq(s21_is_less(number1, number2), returnValueComparison_true);
  ck_assert_uint_eq(s21_is_less(number1, number1), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number2, number2), returnValueComparison_false);
}

END_TEST

START_TEST(s21_is_less_test18) {
  s21_decimal number1 = {{1, 1, 1, 0}};
  s21_decimal number2 = {{1, 1, 1, 0}};
  setScale(&number2, 28);

  ck_assert_uint_eq(s21_is_less(number1, number2), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number1, number1), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number2, number2), returnValueComparison_false);
}

END_TEST

START_TEST(s21_is_less_test19) {
  s21_decimal number1 = {{1, 1, 1, 0}};
  s21_decimal number2 = {{1, 1, 1, 0}};
  setScale(&number2, 29);

  ck_assert_uint_eq(s21_is_less(number1, number2), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number1, number1), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number2, number2), returnValueComparison_false);
}

END_TEST

START_TEST(s21_is_less_test20) {
  s21_decimal number1 = {{1, 1, 1, 0}};
  s21_decimal number2 = {{1, 1, 1, 0}};
  setSign(&number1, 1);
  setSign(&number2, 1);
  setScale(&number2, 28);

  ck_assert_uint_eq(s21_is_less(number1, number2), returnValueComparison_true);
  ck_assert_uint_eq(s21_is_less(number1, number1), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number2, number2), returnValueComparison_false);
}

END_TEST

START_TEST(s21_is_less_test21) {
  s21_decimal number1 = {{1, 1, 1, 0}};
  s21_decimal number2 = {{1, 1, 1, 0}};
  setSign(&number2, 1);
  setSign(&number1, 1);
  setScale(&number2, 29);

  ck_assert_uint_eq(s21_is_less(number1, number2), returnValueComparison_true);
  ck_assert_uint_eq(s21_is_less(number1, number1), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number2, number2), returnValueComparison_false);
}

END_TEST

START_TEST(s21_is_less_test22) {
  s21_decimal number1 = {{1, 1, 1, 0}};
  s21_decimal number2 = {{1, 1, 1, 0}};
  setScale(&number1, 28);
  setScale(&number2, 28);

  ck_assert_uint_eq(s21_is_less(number1, number2), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number1, number1), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number2, number2), returnValueComparison_false);
}

END_TEST

START_TEST(s21_is_less_test23) {
  s21_decimal number1 = {{1, 1, 1, 0}};
  s21_decimal number2 = {{1, 1, 1, 0}};
  setScale(&number1, 29);
  setScale(&number2, 29);

  ck_assert_uint_eq(s21_is_less(number1, number2), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number1, number1), returnValueComparison_false);
  ck_assert_uint_eq(s21_is_less(number2, number2), returnValueComparison_false);
}

END_TEST

START_TEST(s21_is_less_test24) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
}

END_TEST

START_TEST(s21_is_less_test25) {
  s21_decimal a = {{123, 123, 123, 0}};
  s21_decimal b = {{123, 123, 123, 0}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
}

END_TEST

START_TEST(s21_is_less_test26) {
  s21_decimal a = {{123, 0, 0, 0}};
  s21_decimal b = {{123, 0, 0, -2147483648}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
}

END_TEST

START_TEST(s21_is_less_test27) {
  s21_decimal a = {{0xffffffff, 0xffffffff, 0, 1835008}};
  s21_decimal b = {{0xffffffff, 0xfffffffe, 0, 1835008}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
}

END_TEST

START_TEST(s21_is_less_test28) {
  s21_decimal a = {{0xffffffff, 0xffffffff, 0xffffffff, 65536}};
  s21_decimal b = {{0xffffffff, 0xffffffff, 0xffffffff, 196608}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
}

END_TEST

START_TEST(s21_is_less_test29) {
  s21_decimal a = {{0xffffffff, 0xffffffff, 0xffffffff, 65536}};
  s21_decimal b = {{0xffffffff, 0xffffffff, 0xffffffff, 196608}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
}

END_TEST

START_TEST(s21_is_less_test30) {
  s21_decimal a = {{0x99999999, 0xfefefefe, 0xffffffff, -2147483648}};
  s21_decimal b = {{0x99999999, 0xfefefefe, 0xffffffee, -2147483648}};
  ck_assert_int_eq(s21_is_less(a, b), 1);
}

END_TEST

START_TEST(s21_is_less_test31) {
  s21_decimal a = {{12345600, 0, 0, 196608}};
  s21_decimal b = {{123456, 0, 0, 65536}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
}

END_TEST

START_TEST(s21_is_less_test32) {
  s21_decimal a = {{12345678, 0, 0, 0}};
  s21_decimal b = {{123456781, 0, 0, 65536}};
  ck_assert_int_eq(s21_is_less(a, b), 1);
}

END_TEST

START_TEST(s21_is_less_test33) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, -2147483648}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
}

END_TEST

Suite *

is_less_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("is_less");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_is_less_test1);
  tcase_add_test(tc_core, s21_is_less_test2);
  tcase_add_test(tc_core, s21_is_less_test3);
  tcase_add_test(tc_core, s21_is_less_test4);
  tcase_add_test(tc_core, s21_is_less_test5);
  tcase_add_test(tc_core, s21_is_less_test6);
  tcase_add_test(tc_core, s21_is_less_test7);
  tcase_add_test(tc_core, s21_is_less_test8);
  tcase_add_test(tc_core, s21_is_less_test9);
  tcase_add_test(tc_core, s21_is_less_test10);
  tcase_add_test(tc_core, s21_is_less_test11);
  tcase_add_test(tc_core, s21_is_less_test12);
  tcase_add_test(tc_core, s21_is_less_test13);
  tcase_add_test(tc_core, s21_is_less_test14);
  tcase_add_test(tc_core, s21_is_less_test15);
  tcase_add_test(tc_core, s21_is_less_test16);
  tcase_add_test(tc_core, s21_is_less_test17);
  tcase_add_test(tc_core, s21_is_less_test18);
  tcase_add_test(tc_core, s21_is_less_test19);
  tcase_add_test(tc_core, s21_is_less_test20);
  tcase_add_test(tc_core, s21_is_less_test21);
  tcase_add_test(tc_core, s21_is_less_test22);
  tcase_add_test(tc_core, s21_is_less_test23);
  tcase_add_test(tc_core, s21_is_less_test24);
  tcase_add_test(tc_core, s21_is_less_test25);
  tcase_add_test(tc_core, s21_is_less_test26);
  tcase_add_test(tc_core, s21_is_less_test27);
  tcase_add_test(tc_core, s21_is_less_test28);
  tcase_add_test(tc_core, s21_is_less_test29);
  tcase_add_test(tc_core, s21_is_less_test30);
  tcase_add_test(tc_core, s21_is_less_test31);
  tcase_add_test(tc_core, s21_is_less_test32);
  tcase_add_test(tc_core, s21_is_less_test33);
  suite_add_tcase(s, tc_core);
  return s;
}
