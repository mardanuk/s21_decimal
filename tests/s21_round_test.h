#ifndef TEST_HEADER_
#define TEST_HEADER_

#include "../develop/s21_develop.h"
#include "../headers/s21_common.h"
#include "../s21_decimal.h"
#include "math.h"
#include "s21_test.h"

#endif

START_TEST(s21_round_test1) {
  s21_decimal number_2 = {{17111000, 0, 0, 0}};
  s21_decimal result = {0};
  setScale(&number_2, 7);
  int return_number = s21_round(number_2, &result);
  ck_assert_int_eq(return_number, 0);
  ck_assert_int_eq(result.bits[0], 2);
}

END_TEST

START_TEST(s21_round_test2) {
  s21_decimal number_2 = {{UINT32_MAX, 0, UINT32_MAX, 0}};
  setSign(&number_2, 1);
  s21_decimal result = {0};
  int return_number = s21_round(number_2, &result);
  ck_assert_int_eq(return_number, 0);
  ck_assert_int_eq(result.bits[2], UINT32_MAX);
}

END_TEST

START_TEST(s21_round_test3) {
  s21_decimal number_2 = {{0xFFFFFFFF, 0, 0xFFFFFFFF, 0x80020000}};
  s21_decimal result = {0};
  int return_number = s21_round(number_2, &result);
  ck_assert_int_eq(return_number, 0);
}

END_TEST

START_TEST(s21_round_test4) {
  s21_decimal number_2 = {{22, 0, 0, 0}};
  s21_decimal result = {0};
  setScale(&number_2, 1);
  int return_number = s21_round(number_2, &result);
  ck_assert_int_eq(return_number, 0);
  ck_assert_int_eq(result.bits[0], 2);
}

END_TEST

START_TEST(s21_round_test5) {
  s21_decimal number_2 = {{15, 0, 0, pow(2, 16)}};
  s21_decimal result = {0};
  int return_number = s21_round(number_2, &result);
  ck_assert_int_eq(return_number, 0);
}

END_TEST

START_TEST(s21_round_test6) {
  s21_decimal number_2 = {{15, 0, 0, 0x80010000}};
  s21_decimal result = {0};
  int return_number = s21_round(number_2, &result);
  ck_assert_int_eq(return_number, 0);
}

END_TEST

START_TEST(s21_round_test7) {
  s21_decimal number_1 = {{7464923, 0, 0, 0}};
  setScale(&number_1, 5);
  s21_decimal check = {{75, 0, 0, 0}};
  s21_decimal result;
  int return_number = s21_round(number_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_number, errorCodeArithmetic_noError);
}

END_TEST

START_TEST(s21_round_test8) {
  s21_decimal number_1 = {{7444923, 0, 0, 0}};
  setScale(&number_1, 5);
  s21_decimal check = {{74, 0, 0, 0}};
  s21_decimal result;
  int return_number = s21_round(number_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_number, errorCodeArithmetic_noError);
}

END_TEST

START_TEST(s21_round_test9) {
  s21_decimal number_1 = {{7464923, 0, 0, 0}};
  setSign(&number_1, 1);
  setScale(&number_1, 5);
  s21_decimal check = {{75, 0, 0, 0}};
  setSign(&check, 1);
  s21_decimal result;
  int return_number = s21_round(number_1, &result);
  ck_assert_int_eq(result.bits[0], 75);
  ck_assert_int_eq(return_number, errorCodeArithmetic_noError);
}

END_TEST

START_TEST(s21_round_test10) {
  s21_decimal number_1 = {{7444923, 0, 0, 0}};
  setSign(&number_1, 1);
  setScale(&number_1, 5);
  s21_decimal check = {{74, 0, 0, 0}};
  setSign(&check, 1);
  s21_decimal result;
  int return_number = s21_round(number_1, &result);
  ck_assert_int_eq(result.bits[0], 74);
  ck_assert_int_eq(return_number, errorCodeArithmetic_noError);
}

END_TEST

START_TEST(s21_round_test11) {
  s21_decimal src1;
  src1.bits[0] = 0b01010101001110101110101110110001;
  src1.bits[1] = 0b00001101101101001101101001011111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000100100000000000000000;
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000000000001;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal res_od;
  s21_round(src1, &res_od);
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}

END_TEST

START_TEST(s21_round_test12) {
  s21_decimal src1;
  src1.bits[0] = 0b10010111011100111001111111111111;
  src1.bits[1] = 0b00111100000010000011000110001101;
  src1.bits[2] = 0b00000000000000000000000000000001;
  src1.bits[3] = 0b10000000000001110000000000000000;
  s21_decimal res_od;
  s21_round(src1, &res_od);
  s21_decimal result;
  result.bits[3] = 0b10000000000000000000000000000000;
  result.bits[2] = 0;
  result.bits[1] = 0b00000000000000000000001000010010;
  result.bits[0] = 0b00110110101101101000110001000000;
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}

END_TEST

START_TEST(s21_round_test13) {
  int a = 0;
  s21_decimal my_decimal_1 = {{624545, 0, 0, 2147745792}};  // exp = 4
  s21_decimal check_number = {{0, 0, 0, 0}};
  s21_decimal otvet = {{62, 0, 0, 2147483648}};
  int my_result = s21_round(my_decimal_1, &check_number);
  ck_assert_int_eq(my_result, a);
  ck_assert_int_eq(otvet.bits[3], check_number.bits[3]);
  ck_assert_int_eq(otvet.bits[2], check_number.bits[2]);
  ck_assert_int_eq(otvet.bits[1], check_number.bits[1]);
  ck_assert_int_eq(otvet.bits[0], check_number.bits[0]);
}

END_TEST

START_TEST(s21_round_test14) {
  int a = 0;
  s21_decimal my_decimal_1 = {{2147483648, 0, 0, 65536}};
  s21_decimal check_number = {{0, 0, 0, 0}};
  s21_decimal otvet = {{214748365, 0, 0, 0}};
  int my_result = s21_round(my_decimal_1, &check_number);
  ck_assert_int_eq(my_result, a);
  ck_assert_int_eq(otvet.bits[3], check_number.bits[3]);
  ck_assert_int_eq(otvet.bits[2], check_number.bits[2]);
  ck_assert_int_eq(otvet.bits[1], check_number.bits[1]);
  ck_assert_int_eq(otvet.bits[0], check_number.bits[0]);
}

END_TEST

START_TEST(s21_round_test15) {
  int a = 0;
  s21_decimal my_decimal_1 = {{100, 0, 0, 65536}};
  s21_decimal check_number = {{0, 0, 0, 0}};
  s21_decimal otvet = {{10, 0, 0, 0}};
  int my_result = s21_round(my_decimal_1, &check_number);
  ck_assert_int_eq(my_result, a);
  ck_assert_int_eq(otvet.bits[3], check_number.bits[3]);
  ck_assert_int_eq(otvet.bits[2], check_number.bits[2]);
  ck_assert_int_eq(otvet.bits[1], check_number.bits[1]);
  ck_assert_int_eq(otvet.bits[0], check_number.bits[0]);
}

END_TEST

START_TEST(s21_round_test16) {
  int a = 0;
  s21_decimal my_decimal_1 = {{105, 0, 0, 2147942400}};
  s21_decimal check_number = {{0, 0, 0, 0}};
  s21_decimal otvet = {{0, 0, 0, 2147483648}};
  int my_result = s21_round(my_decimal_1, &check_number);
  ck_assert_int_eq(my_result, a);
  ck_assert_int_eq(otvet.bits[3], check_number.bits[3]);
  ck_assert_int_eq(otvet.bits[2], check_number.bits[2]);
  ck_assert_int_eq(otvet.bits[1], check_number.bits[1]);
  ck_assert_int_eq(otvet.bits[0], check_number.bits[0]);
}

END_TEST

START_TEST(s21_round_test17) {
  int a = 0;
  s21_decimal my_decimal_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 65536}};
  s21_decimal check_number = {{0, 0, 0, 0}};
  s21_decimal otvet = {{0x9999999A, 0x99999999, 0x19999999, 0}};
  int my_result = s21_round(my_decimal_1, &check_number);
  ck_assert_int_eq(my_result, a);
  ck_assert_int_eq(otvet.bits[3], check_number.bits[3]);
  ck_assert_int_eq(otvet.bits[2], check_number.bits[2]);
  ck_assert_int_eq(otvet.bits[1], check_number.bits[1]);
  ck_assert_int_eq(otvet.bits[0], check_number.bits[0]);
}

END_TEST

START_TEST(s21_round_test18) {
  int a = 0;
  s21_decimal my_decimal_1 = {{20765485, 0, 0, 0x80040000}};  // exp = 4, neg
  s21_decimal check_number = {{0, 0, 0, 0}};
  s21_decimal otvet = {{2077, 0, 0, 2147483648}};
  int my_result = s21_round(my_decimal_1, &check_number);
  ck_assert_int_eq(my_result, a);
  ck_assert_int_eq(otvet.bits[3], check_number.bits[3]);
  ck_assert_int_eq(otvet.bits[2], check_number.bits[2]);
  ck_assert_int_eq(otvet.bits[1], check_number.bits[1]);
  ck_assert_int_eq(otvet.bits[0], check_number.bits[0]);
}

END_TEST

START_TEST(s21_round_test19) {
  s21_decimal input = {{0, 0, 0, 0}};
  setScale(&input, 15);
  s21_decimal expected = {{0}};
  s21_decimal result;
  s21_round(input, &result);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

START_TEST(s21_round_test20) {
  s21_decimal input = {{362732873, 0, 0, 0}};
  setSign(&input, 1);
  s21_decimal expected = {{362732873, 0, 0, 0}};
  setSign(&expected, 1);
  s21_decimal result;
  s21_round(input, &result);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

START_TEST(s21_round_test21) {
  s21_decimal input = {{45, 0, 0, 0}};
  setScale(&input, 1);
  s21_decimal expected = {{5, 0, 0, 0}};
  s21_decimal result;
  s21_round(input, &result);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

START_TEST(s21_round_test22) {
  s21_decimal input = {{0xb54ac285, 0x9bde85, 0, 0}};
  setSign(&input, 1);
  setScale(&input, 8);
  s21_decimal expected = {{0x1a268848, 0, 0, 0}};
  setSign(&expected, 1);
  s21_decimal result;
  s21_round(input, &result);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

START_TEST(s21_round_test23) {
  s21_decimal input = {{0x4C577A00, 0xC0D845D, 0, 0}};
  setScale(&input, 8);
  s21_decimal expected = {{0x5A9F2BA, 0x2, 0, 0}};
  s21_decimal result;
  s21_round(input, &result);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

START_TEST(s21_round_test24) {
  s21_decimal input = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  setSign(&input, 1);
  setScale(&input, 28);
  s21_decimal expected = {{8, 0, 0, 0}};
  setSign(&expected, 1);
  s21_decimal result;
  s21_round(input, &result);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

Suite *round_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("round");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_round_test1);
  tcase_add_test(tc_core, s21_round_test2);
  tcase_add_test(tc_core, s21_round_test3);
  tcase_add_test(tc_core, s21_round_test4);
  tcase_add_test(tc_core, s21_round_test5);
  tcase_add_test(tc_core, s21_round_test6);
  tcase_add_test(tc_core, s21_round_test7);
  tcase_add_test(tc_core, s21_round_test8);
  tcase_add_test(tc_core, s21_round_test9);
  tcase_add_test(tc_core, s21_round_test10);
  tcase_add_test(tc_core, s21_round_test11);
  tcase_add_test(tc_core, s21_round_test12);
  tcase_add_test(tc_core, s21_round_test13);
  tcase_add_test(tc_core, s21_round_test14);
  tcase_add_test(tc_core, s21_round_test15);
  tcase_add_test(tc_core, s21_round_test16);
  tcase_add_test(tc_core, s21_round_test17);
  tcase_add_test(tc_core, s21_round_test18);
  tcase_add_test(tc_core, s21_round_test19);
  tcase_add_test(tc_core, s21_round_test20);
  tcase_add_test(tc_core, s21_round_test21);
  tcase_add_test(tc_core, s21_round_test22);
  tcase_add_test(tc_core, s21_round_test23);
  tcase_add_test(tc_core, s21_round_test24);
  suite_add_tcase(s, tc_core);
  return s;
}
