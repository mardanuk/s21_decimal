#ifndef TEST_HEADER_
#define TEST_HEADER_

#include "../develop/s21_develop.h"
#include "../headers/s21_common.h"
#include "../s21_decimal.h"
#include "s21_test.h"

#endif

START_TEST(s21_floor_test1) {
  s21_decimal number_2 = {{0xFFFFFFFF, 0, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {0};
  int return_number = s21_floor(number_2, &result);
  ck_assert_int_eq(return_number, 0);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
}

END_TEST

START_TEST(s21_floor_test2) {
  s21_decimal number_2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0x80010000}};
  s21_decimal result = {0};
  int return_number = s21_floor(number_2, &result);
  ck_assert_int_eq(return_number, 0);
}

END_TEST

START_TEST(s21_floor_test3) {
  s21_decimal number_2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal result = {0};
  int return_number = s21_floor(number_2, &result);
  ck_assert_int_eq(return_number, 0);
}

END_TEST

START_TEST(s21_floor_test4) {
  s21_decimal number_2 = {{UINT_MAX, UINT_MAX, 0, 0x80010000}};
  s21_decimal result = {0};
  int return_number = s21_floor(number_2, &result);
  ck_assert_int_eq(return_number, 0);
}

END_TEST

START_TEST(s21_floor_test5) {
  s21_decimal number_1 = {{7444923, 0, 0, 0}};
  setScale(&number_1, 5);
  s21_decimal check = {{74, 0, 0, 0}};
  s21_decimal result;
  int return_number = s21_floor(number_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_number, errorCodeArithmetic_noError);
}

END_TEST

START_TEST(s21_floor_test6) {
  s21_decimal number_1 = {{7444923, 0, 0, 0}};
  setScale(&number_1, 5);
  setSign(&number_1, 1);
  s21_decimal check = {{75, 0, 0, 0}};
  setSign(&check, 1);
  s21_decimal result;
  int return_number = s21_floor(number_1, &result);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_number, errorCodeArithmetic_noError);
}

END_TEST

START_TEST(s21_floor_test7) {
  s21_decimal src1;
  src1.bits[0] = 0b00001111111111111111111111111111;
  src1.bits[1] = 0b00111110001001010000001001100001;
  src1.bits[2] = 0b00100000010011111100111001011110;
  src1.bits[3] = 0b10000000000010100000000000000000;
  s21_decimal res_od;
  s21_floor(src1, &res_od);
  s21_decimal result;
  result.bits[0] = 0b10100111011001000000000000000000;
  result.bits[1] = 0b00001101111000001011011010110011;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}

END_TEST

START_TEST(s21_floor_test8) {
  int a = 0;
  s21_decimal my_decimal_1 = {{65365, 0, 0, 0x00040000}};
  s21_decimal check_number = {{0, 0, 0, 0}};
  s21_decimal otvet = {{6, 0, 0, 0}};
  int my_result = s21_floor(my_decimal_1, &check_number);
  ck_assert_int_eq(my_result, a);
  ck_assert_int_eq(otvet.bits[3], check_number.bits[3]);
  ck_assert_int_eq(otvet.bits[2], check_number.bits[2]);
  ck_assert_int_eq(otvet.bits[1], check_number.bits[1]);
  ck_assert_int_eq(otvet.bits[0], check_number.bits[0]);
}

END_TEST

START_TEST(s21_floor_test9) {
  int a = 0;
  s21_decimal my_decimal_1 = {{0, 0, 0, 0x00040000}};
  s21_decimal check_number = {{0, 0, 0, 0}};
  s21_decimal otvet = {{0, 0, 0, 0}};
  int my_result = s21_floor(my_decimal_1, &check_number);
  ck_assert_int_eq(my_result, a);
  ck_assert_int_eq(otvet.bits[3], check_number.bits[3]);
  ck_assert_int_eq(otvet.bits[2], check_number.bits[2]);
  ck_assert_int_eq(otvet.bits[1], check_number.bits[1]);
  ck_assert_int_eq(otvet.bits[0], check_number.bits[0]);
}

END_TEST

START_TEST(s21_floor_test10) {
  int a = 0;
  s21_decimal my_decimal_1 = {{6123, 0, 0, 2147942400}};
  s21_decimal check_number = {{0, 0, 0, 0}};
  s21_decimal otvet = {{1, 0, 0, 2147483648}};
  int my_result = s21_floor(my_decimal_1, &check_number);
  ck_assert_int_eq(my_result, a);
  ck_assert_int_eq(otvet.bits[3], check_number.bits[3]);
  ck_assert_int_eq(otvet.bits[2], check_number.bits[2]);
  ck_assert_int_eq(otvet.bits[1], check_number.bits[1]);
  ck_assert_int_eq(otvet.bits[0], check_number.bits[0]);
}

END_TEST

START_TEST(s21_floor_test11) {
  int a = 0;
  s21_decimal my_decimal_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 65536}};
  s21_decimal check_number = {{0, 0, 0, 0}};
  s21_decimal otvet = {{0x99999999, 0x99999999, 0x19999999, 0}};
  int my_result = s21_floor(my_decimal_1, &check_number);
  ck_assert_int_eq(my_result, a);
  ck_assert_int_eq(otvet.bits[3], check_number.bits[3]);
  ck_assert_int_eq(otvet.bits[2], check_number.bits[2]);
  ck_assert_int_eq(otvet.bits[1], check_number.bits[1]);
  ck_assert_int_eq(otvet.bits[0], check_number.bits[0]);
}

END_TEST

START_TEST(s21_floor_test12) {
  int a = 0;
  s21_decimal my_decimal_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  s21_decimal check_number = {{0, 0, 0, 0}};
  s21_decimal otvet = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  int my_result = s21_floor(my_decimal_1, &check_number);
  ck_assert_int_eq(my_result, a);
  ck_assert_int_eq(otvet.bits[3], check_number.bits[3]);
  ck_assert_int_eq(otvet.bits[2], check_number.bits[2]);
  ck_assert_int_eq(otvet.bits[1], check_number.bits[1]);
  ck_assert_int_eq(otvet.bits[0], check_number.bits[0]);
}

END_TEST

START_TEST(s21_floor_test13) {
  int a = 0;
  s21_decimal my_decimal_1 = {{1, 0, 0, 2147483648}};
  s21_decimal check_number = {{0, 0, 0, 0}};
  s21_decimal otvet = {{1, 0, 0, 2147483648}};
  int my_result = s21_floor(my_decimal_1, &check_number);
  ck_assert_int_eq(my_result, a);
  ck_assert_int_eq(otvet.bits[3], check_number.bits[3]);
  ck_assert_int_eq(otvet.bits[2], check_number.bits[2]);
  ck_assert_int_eq(otvet.bits[1], check_number.bits[1]);
  ck_assert_int_eq(otvet.bits[0], check_number.bits[0]);
}

END_TEST

START_TEST(s21_floor_test14) {
  s21_decimal input = {{0, 0, 0, 0}};
  setScale(&input, 15);
  s21_decimal expected = {{0, 0, 0, 0}};
  s21_decimal result;
  s21_floor(input, &result);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

START_TEST(s21_floor_test15) {
  s21_decimal input = {{362732873, 0, 0, 0}};
  s21_decimal expected = {{362732873, 0, 0, 0}};
  setSign(&input, 1);
  setSign(&expected, 1);
  s21_decimal result;
  s21_floor(input, &result);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

START_TEST(s21_floor_test16) {
  s21_decimal input = {{572963473, 0, 0, 0}};
  setScale(&input, 4);
  s21_decimal expected = {{57296, 0, 0, 0}};
  s21_decimal result;
  s21_floor(input, &result);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

START_TEST(s21_floor_test17) {
  s21_decimal input = {{0xb54ac285, 0x9bde85, 0, 0}};
  setScale(&input, 8);
  s21_decimal expected = {{0x1a268849, 0, 0, 0}};
  setSign(&input, 1);
  setSign(&expected, 1);
  s21_decimal result;
  s21_floor(input, &result);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

START_TEST(s21_floor_test18) {
  s21_decimal input = {{0x4C577A00, 0xC0D845D, 0, 0}};
  setScale(&input, 8);
  s21_decimal expected = {{0x5A9F2BA, 0x2, 0, 0}};
  s21_decimal result;
  s21_floor(input, &result);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

START_TEST(s21_floor_test19) {
  s21_decimal input = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  setScale(&input, 28);
  s21_decimal expected = {{8, 0, 0, 0}};
  setSign(&input, 1);
  setSign(&expected, 1);
  s21_decimal result;
  s21_floor(input, &result);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

Suite *floor_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("floor");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_floor_test1);
  tcase_add_test(tc_core, s21_floor_test2);
  tcase_add_test(tc_core, s21_floor_test3);
  tcase_add_test(tc_core, s21_floor_test4);
  tcase_add_test(tc_core, s21_floor_test5);
  tcase_add_test(tc_core, s21_floor_test6);
  tcase_add_test(tc_core, s21_floor_test7);
  tcase_add_test(tc_core, s21_floor_test8);
  tcase_add_test(tc_core, s21_floor_test9);
  tcase_add_test(tc_core, s21_floor_test10);
  tcase_add_test(tc_core, s21_floor_test11);
  tcase_add_test(tc_core, s21_floor_test12);
  tcase_add_test(tc_core, s21_floor_test13);
  tcase_add_test(tc_core, s21_floor_test14);
  tcase_add_test(tc_core, s21_floor_test15);
  tcase_add_test(tc_core, s21_floor_test16);
  tcase_add_test(tc_core, s21_floor_test17);
  tcase_add_test(tc_core, s21_floor_test18);
  tcase_add_test(tc_core, s21_floor_test19);
  suite_add_tcase(s, tc_core);
  return s;
}
