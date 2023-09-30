#ifndef TEST_HEADER_
#define TEST_HEADER_

#include "../develop/s21_develop.h"
#include "../s21_decimal.h"
#include "s21_test.h"

#endif

// 64438.2323 * 21.1 = 1359646.70153
START_TEST(s21_mul_test1) {
  s21_decimal input1 = {{0x26687e73, 0, 0, 0}};
  s21_decimal input2 = {{0xd3, 0, 0, 0}};
  s21_decimal expected = {{0xa82038c9, 0x1f, 0, 0}};

  setScale(&input1, 4);
  setScale(&input2, 1);
  setScale(&expected, 5);

  s21_decimal result;
  int status = s21_mul(input1, input2, &result);

  ck_assert_int_eq(status, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

// -10.24 * 10.24 = 104.8576
START_TEST(s21_mul_test2) {
  s21_decimal input1 = {{0x400, 0, 0, 0}};
  s21_decimal input2 = {{0x400, 0, 0, 0}};
  s21_decimal expected = {{0x100000, 0, 0, 0}};
  s21_decimal result;

  setScale(&input1, 2);
  setScale(&input2, 2);
  setScale(&expected, 4);

  setSign(&input1, 1);
  setSign(&input2, 1);
  setSign(&expected, 0);

  int status = s21_mul(input1, input2, &result);
  ck_assert_int_eq(status, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

// 1e-28 * 1e-28 = 0
START_TEST(s21_mul_test3) {
  s21_decimal input1 = {{0x1, 0, 0, 0}};
  s21_decimal input2 = {{0x1, 0, 0, 0}};
  s21_decimal expected = {{0x0, 0, 0, 0}};
  s21_decimal result;

  setScale(&input1, 28);
  setScale(&input2, 28);
  setScale(&expected, 28);

  setSign(&input1, 0);
  setSign(&input2, 0);
  setSign(&expected, 0);

  int status = s21_mul(input1, input2, &result);
  ck_assert_int_eq(status, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

// 1e-14 * 1e-14 = 1e-28
START_TEST(s21_mul_test4) {
  s21_decimal input1 = {{0x1, 0, 0, 0}};
  s21_decimal input2 = {{0x1, 0, 0, 0}};
  s21_decimal expected = {{0x1, 0, 0, 0}};
  s21_decimal result;

  setScale(&input1, 14);
  setScale(&input2, 14);
  setScale(&expected, 28);

  setSign(&input1, 1);
  setSign(&input2, 1);
  setSign(&expected, 0);

  int status = s21_mul(input1, input2, &result);
  ck_assert_int_eq(status, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

// 6e-15 * 1e-14 = 1e-28
START_TEST(s21_mul_test5) {
  s21_decimal input1 = {{0x6, 0, 0, 0}};
  s21_decimal input2 = {{0x1, 0, 0, 0}};
  s21_decimal expected = {{0x1, 0, 0, 0}};
  s21_decimal result;

  setScale(&input1, 15);
  setScale(&input2, 14);
  setScale(&expected, 28);

  setSign(&input1, 1);
  setSign(&input2, 1);
  setSign(&expected, 0);

  int status = s21_mul(input1, input2, &result);
  ck_assert_int_eq(status, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

// 0 * -42949672.95 = 0
START_TEST(s21_mul_test6) {
  s21_decimal input1 = {{0}};
  s21_decimal input2 = {{0xffffffff, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 0, 0}};
  s21_decimal result;

  setScale(&input1, 0);
  setScale(&input2, 2);
  setScale(&expected, 2);

  setSign(&input1, 0);
  setSign(&input2, 1);
  setSign(&expected, 1);

  int status = s21_mul(input1, input2, &result);
  ck_assert_int_eq(status, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

// 18446744073709.551615 * 1 = 18446744073709.551615
START_TEST(s21_mul_test7) {
  s21_decimal input1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0}};
  s21_decimal input2 = {{1}};
  s21_decimal expected = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0}};
  s21_decimal result;

  setScale(&input1, 6);
  setScale(&input2, 0);
  setScale(&expected, 6);

  setSign(&input1, 1);
  setSign(&input2, 0);
  setSign(&expected, 1);

  int status = s21_mul(input1, input2, &result);
  ck_assert_int_eq(status, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

// 644388461.24564323 * 100 = 64438846124.56432300
START_TEST(s21_mul_test8) {
  s21_decimal input1 = {{0x4fd9f63, 0xe4eeca, 0, 0}};
  s21_decimal input2 = {{0x64, 0, 0, 0}};
  s21_decimal expected = {{0xf31242ac, 0x596d46e9, 0, 0}};
  s21_decimal result;

  setScale(&input1, 8);
  setScale(&input2, 0);
  setScale(&expected, 8);

  setSign(&input1, 0);
  setSign(&input2, 0);
  setSign(&expected, 0);

  int status = s21_mul(input1, input2, &result);
  ck_assert_int_eq(status, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

// 75628.4783749104619446 * 7562849.389272378 = 571966791489.29083373022722365
START_TEST(s21_mul_test9) {
  s21_decimal input1 = {{0xee7f4fb6, 0xff8f4bd9, 0x28, 0}};
  s21_decimal input2 = {{0x17565d3a, 0x1ade5f, 0, 0}};
  s21_decimal expected = {{0xebedb93d, 0x9c7bbf94, 0xb8cffbed, 0}};
  s21_decimal result;

  setScale(&input1, 16);
  setScale(&input2, 9);
  setScale(&expected, 17);

  setSign(&input1, 0);
  setSign(&input2, 0);
  setSign(&expected, 0);

  int status = s21_mul(input1, input2, &result);
  ck_assert_int_eq(status, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

// 75628.478374910555555 * 7562849.389555555 = 571966791510.70778731235573959
START_TEST(s21_mul_test10) {
  s21_decimal input1 = {{0x97daf5a3, 0x198e5462, 0x4, 0}};
  s21_decimal input2 = {{0x175aaf63, 0x1ade5f, 0, 0}};
  s21_decimal expected = {{0xaf4f00c6, 0xba349429, 0xb8cffbed, 0}};
  s21_decimal result;

  setScale(&input1, 15);
  setScale(&input2, 9);
  setScale(&expected, 17);

  setSign(&input1, 0);
  setSign(&input2, 0);
  setSign(&expected, 0);

  int status = s21_mul(input1, input2, &result);
  ck_assert_int_eq(status, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

// -7.9228162514264337593543950335 * 7.9228162514264337593543950335 =
// -62.771017353866807638357894230
START_TEST(s21_mul_test11) {
  s21_decimal input1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal input2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal expected = {{0x96EE456, 0x359A3B3E, 0xCAD2F7F5, 0}};
  s21_decimal result;

  setScale(&input1, 28);
  setScale(&input2, 28);
  setScale(&expected, 27);

  setSign(&input1, 1);
  setSign(&input2, 0);
  setSign(&expected, 1);

  int status = s21_mul(input1, input2, &result);
  ck_assert_int_eq(status, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

// 27824724378.43634677634 * 46513.1237326723 = 1294214847841713.1524935845060
START_TEST(s21_mul_test12) {
  s21_decimal input1 = {{0x4903e782, 0xd68fe40c, 0x96, 0}};
  s21_decimal input2 = {{0xce2cbf83, 0x1a708, 0, 0}};
  s21_decimal expected = {{0xffa304c4, 0xd8b3a201, 0x29d17e8a, 0}};
  s21_decimal result;

  setScale(&input1, 11);
  setScale(&input2, 10);
  setScale(&expected, 13);

  setSign(&input1, 1);
  setSign(&input2, 0);
  setSign(&expected, 1);

  int status = s21_mul(input1, input2, &result);

  ck_assert_int_eq(status, errorCodeArithmetic_noError);
  ASSERT_DECIMAL_EQ(result, expected)
}

// 79228162514264337593543950335 * 1.1 = INF
START_TEST(s21_mul_test13) {
  s21_decimal input1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal input2 = {{11, 0, 0, 0}};
  s21_decimal result;

  setScale(&input1, 0);
  setScale(&input2, 1);

  setSign(&input1, 0);
  setSign(&input2, 0);

  int status = s21_mul(input1, input2, &result);

  ck_assert_int_eq(status, errorCodeArithmetic_tooLargeOrInfinity);
}

// -79228162514264337593543950335 * 79228162514264337593543950335 = -INF
START_TEST(s21_mul_test14) {
  s21_decimal input1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal input2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal result;

  setScale(&input1, 0);
  setScale(&input2, 0);

  setSign(&input1, 1);
  setSign(&input2, 0);

  int status = s21_mul(input1, input2, &result);

  ck_assert_int_eq(status, errorCodeArithmetic_tooSmallOrNegativeInfinity);
}

Suite *mul_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("mul");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_mul_test1);
  tcase_add_test(tc_core, s21_mul_test2);
  tcase_add_test(tc_core, s21_mul_test3);
  tcase_add_test(tc_core, s21_mul_test4);
  tcase_add_test(tc_core, s21_mul_test5);
  tcase_add_test(tc_core, s21_mul_test6);
  tcase_add_test(tc_core, s21_mul_test7);
  tcase_add_test(tc_core, s21_mul_test8);
  tcase_add_test(tc_core, s21_mul_test9);
  tcase_add_test(tc_core, s21_mul_test10);
  tcase_add_test(tc_core, s21_mul_test11);
  tcase_add_test(tc_core, s21_mul_test12);
  tcase_add_test(tc_core, s21_mul_test13);
  tcase_add_test(tc_core, s21_mul_test14);
  suite_add_tcase(s, tc_core);
  return s;
}
