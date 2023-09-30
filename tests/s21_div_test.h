#ifndef TEST_HEADER_
#define TEST_HEADER_

#include "../develop/s21_develop.h"
#include "../s21_decimal.h"
#include "s21_test.h"

#endif

// 4294967295 / 0 = NaN
START_TEST(s21_div_test1) {
  s21_decimal input1 = {{0xFFFFFFFF, 0, 0, 0}};
  s21_decimal input2 = {{0, 0, 0, 0}};
  s21_decimal result;
  setSign(&input1, 0);
  setSign(&input2, 1);
  setScale(&input1, 2);
  setScale(&input2, 23);
  int status = s21_div(input1, input2, &result);
  ck_assert_int_eq(status, errorCodeArithmetic_divisionByZero);
}

END_TEST

// 0.0000 / 7.5 = 0
START_TEST(s21_div_test2) {
  s21_decimal input1 = {{0, 0, 0, 0}};
  s21_decimal input2 = {{75, 0, 0, 0}};
  s21_decimal result;

  setSign(&input1, 0);
  setSign(&input2, 0);
  setScale(&input1, 4);
  setScale(&input2, 1);

  int status = s21_div(input1, input2, &result);
  ck_assert_int_eq(status, errorCodeArithmetic_noError);
}

END_TEST

// 2.25 / -1.5 = -1.5
START_TEST(s21_div_test3) {
  s21_decimal input1 = {{225, 0, 0, 0}};
  s21_decimal input2 = {{15, 0, 0, 0}};
  s21_decimal expected = {{15, 0, 0, 0}};
  s21_decimal result;

  setSign(&input1, 0);
  setSign(&input2, 1);
  setSign(&expected, 1);
  setScale(&input1, 2);
  setScale(&input2, 1);
  setScale(&expected, 1);

  int status = s21_div(input1, input2, &result);
  ck_assert_int_eq(status, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

// 2 / 3 = 0.6666666666666666666666666667
START_TEST(s21_div_test4) {
  s21_decimal input1 = {{2, 0, 0, 0}};
  s21_decimal input2 = {{3, 0, 0, 0}};
  s21_decimal expected = {{0xaaaaaab, 0x296e0196, 0x158a8994, 0}};
  s21_decimal result;

  setSign(&input1, 0);
  setSign(&input2, 0);
  setSign(&expected, 0);
  setScale(&input1, 0);
  setScale(&input2, 0);
  setScale(&expected, 28);

  int status = s21_div(input1, input2, &result);
  ck_assert_int_eq(status, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

// 1e-28 / 5 = 0
START_TEST(s21_div_test5) {
  s21_decimal input1 = {{1, 0, 0, 0}};
  s21_decimal input2 = {{5, 0, 0, 0}};
  s21_decimal expected = {{0}};
  s21_decimal result;

  setSign(&input1, 0);
  setSign(&input2, 0);
  setSign(&expected, 0);
  setScale(&input1, 28);
  setScale(&input2, 0);
  setScale(&expected, 0);

  int status = s21_div(input1, input2, &result);
  ck_assert_int_eq(status, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

// 20 / 1e-5 = 400000
START_TEST(s21_div_test6) {
  s21_decimal input1 = {{20, 0, 0, 0}};
  s21_decimal input2 = {{5, 0, 0, 0}};
  s21_decimal expected = {{400000}};
  s21_decimal result;

  setSign(&input1, 0);
  setSign(&input2, 0);
  setSign(&expected, 0);
  setScale(&input1, 0);
  setScale(&input2, 5);
  setScale(&expected, 0);

  int status = s21_div(input1, input2, &result);
  ck_assert_int_eq(status, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

// Too much precision
// 4449249363747.434387 / 43764 = 101664595.64362111294671419431
START_TEST(s21_div_test7) {
  s21_decimal input1 = {{0x234C6F93, 0x3DBEE8B9, 0, 0}};
  s21_decimal input2 = {{0xAAF4, 0, 0, 0}};
  s21_decimal expected = {{0x373BF827 + 1, 0x4ef17458, 0x20d97f8d, 0}};
  s21_decimal result;

  setSign(&input1, 0);
  setSign(&input2, 0);
  setSign(&expected, 0);
  setScale(&input1, 0);
  setScale(&input2, 6);
  setScale(&expected, 8);

  int status = s21_div(input1, input2, &result);
  ck_assert_int_eq(status, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

// -936582642837 / 0.1041747302401649 = -8990497414083.03230156190427
START_TEST(s21_div_test8) {
  s21_decimal input1 = {{0x10ACFC95, 0xDA, 0, 0}};
  s21_decimal input2 = {{0xB1E7C671, 0x3B376, 0, 0}};
  s21_decimal expected = {{0x662EB2DB, 0x23EF54FF, 0x2E7AD30, 0}};
  s21_decimal result;

  setSign(&input1, 1);
  setSign(&input2, 0);
  setSign(&expected, 1);
  setScale(&input1, 0);
  setScale(&input2, 16);
  setScale(&expected, 14);

  int status = s21_div(input1, input2, &result);
  ck_assert_int_eq(status, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

// -0.3183718237812378127 / -0.3183718237812378127 = 1
START_TEST(s21_div_test9) {
  s21_decimal input1 = {{0x85BD4A0F, 0x2c2ed6de, 0, 0}};
  s21_decimal input2 = {{0x85BD4A0F, 0x2c2ed6de, 0, 0}};
  s21_decimal expected = {{1}};
  s21_decimal result;

  setSign(&input1, 1);
  setSign(&input2, 1);
  setSign(&expected, 0);
  setScale(&input1, 19);
  setScale(&input2, 19);
  setScale(&expected, 0);

  int status = s21_div(input1, input2, &result);
  ck_assert_int_eq(status, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

// 948347948.43877834 / 1e+16 = 9.4834794843877834e-11
START_TEST(s21_div_test10) {
  s21_decimal input1 = {{0x530431CA, 0x150EBBE, 0, 0}};
  s21_decimal input2 = {{0x89E80000, 0x8AC72304}};
  s21_decimal expected = {{0x530431CA, 0x150EBBE, 0, 0}};
  s21_decimal result = {{0}};

  setSign(&input1, 1);
  setSign(&input2, 1);
  setSign(&expected, 0);
  setScale(&input1, 8);
  setScale(&input2, 27);
  setScale(&expected, 0);

  int status = s21_div(input1, input2, &result);
  ck_assert_int_eq(status, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

// -184838746726726348023 / 0.00000000193289 = -INF
START_TEST(s21_div_test11) {
  s21_decimal input1 = {{0x8EEBACF7, 0x52724D4, 0xA, 0}};
  s21_decimal input2 = {{0x2F309, 0, 0, 0}};
  s21_decimal result;

  setSign(&input1, 1);
  setSign(&input2, 0);
  setScale(&input1, 0);
  setScale(&input2, 14);

  int status = s21_div(input1, input2, &result);
  ck_assert_int_eq(status, errorCodeArithmetic_tooSmallOrNegativeInfinity);
}

END_TEST

// 45284674874386437639m / 0.00000000048934 = INF
START_TEST(s21_div_test12) {
  s21_decimal input1 = {{0xA8DC5607, 0x4737BDEA, 0x27, 0}};
  s21_decimal input2 = {{0x2F309, 0, 0, 0}};
  s21_decimal result;

  setSign(&input1, 0);
  setSign(&input2, 0);
  setScale(&input1, 0);
  setScale(&input2, 14);

  int status = s21_div(input1, input2, &result);
  ck_assert_int_eq(status, errorCodeArithmetic_tooLargeOrInfinity);
}

END_TEST

// 75384834.34934734873487 / 1349.34984 = 55867.52383603302516037649658
START_TEST(s21_div_test13) {
  s21_decimal input1 = {{0xE36AE38F, 0xA9793779, 0x198, 0}};
  s21_decimal input2 = {{0x80AF1C8, 0, 0, 0}};
  s21_decimal expected = {{0x972204FA, 0x9272C199, 0x120D40D5, 0}};
  s21_decimal result;

  setSign(&input1, 0);
  setSign(&input2, 0);
  setSign(&expected, 0);
  setScale(&input1, 14);
  setScale(&input2, 5);
  setScale(&expected, 23);

  int status = s21_div(input1, input2, &result);
  ck_assert_int_eq(status, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

// 7.9228162514264337593543950335 / 0.5 = 15.845632502852867518708790067
START_TEST(s21_div_test14) {
  s21_decimal input1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal input2 = {{5, 0, 0, 0}};
  s21_decimal expected = {{0x33333333, 0x33333333, 0x33333333, 0}};
  s21_decimal result;

  setSign(&input1, 0);
  setSign(&input2, 0);
  setSign(&expected, 0);
  setScale(&input1, 28);
  setScale(&input2, 1);
  setScale(&expected, 27);

  int status = s21_div(input1, input2, &result);
  ck_assert_int_eq(status, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

// 7922816251426433759354395033.5 / 0.01 = INF
START_TEST(s21_div_test15) {
  s21_decimal input1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal input2 = {{1, 0, 0, 0}};
  s21_decimal result;

  setSign(&input1, 0);
  setSign(&input2, 0);
  setScale(&input1, 1);
  setScale(&input2, 2);

  int status = s21_div(input1, input2, &result);
  ck_assert_int_eq(status, errorCodeArithmetic_tooLargeOrInfinity);
}

END_TEST

Suite *div_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("div");
  tc_core = tcase_create("core");

  tcase_add_test(tc_core, s21_div_test1);
  tcase_add_test(tc_core, s21_div_test2);
  tcase_add_test(tc_core, s21_div_test3);
  tcase_add_test(tc_core, s21_div_test4);
  tcase_add_test(tc_core, s21_div_test5);
  tcase_add_test(tc_core, s21_div_test6);
  tcase_add_test(tc_core, s21_div_test7);
  tcase_add_test(tc_core, s21_div_test8);
  tcase_add_test(tc_core, s21_div_test9);
  tcase_add_test(tc_core, s21_div_test10);
  tcase_add_test(tc_core, s21_div_test11);
  tcase_add_test(tc_core, s21_div_test12);
  tcase_add_test(tc_core, s21_div_test13);
  tcase_add_test(tc_core, s21_div_test14);
  tcase_add_test(tc_core, s21_div_test15);
  suite_add_tcase(s, tc_core);
  return s;
}
