#ifndef TEST_HEADER_
#define TEST_HEADER_

#include "../develop/s21_develop.h"
#include "../headers/s21_common.h"
#include "../s21_decimal.h"
#include "s21_test.h"

#endif

START_TEST(s21_truncate_test1) {
  s21_decimal number_2 = {{0, 0, 0, 0x80020000}};
  s21_decimal number_1 = {0};
  setSign(&number_1, 1);
  s21_decimal result = {0};
  int return_number = s21_truncate(number_2, &result);
  ck_assert_int_eq(return_number, 0);
  ck_assert_int_eq(s21_is_equal(result, number_1), 1);
}

END_TEST

START_TEST(s21_truncate_test2) {
  s21_decimal number_2 = {{1111000, 0, 0, 0}};
  s21_decimal number_1 = {0};
  s21_decimal result = {0};
  setScale(&number_2, 7);
  int return_number = s21_truncate(number_2, &result);
  ck_assert_int_eq(return_number, 0);
  ck_assert_int_eq(s21_is_equal(result, number_1), 1);
}

END_TEST

START_TEST(s21_truncate_test3) {
  s21_decimal number_1 = {{35, 0, 0, 0}};
  s21_decimal check = {{3, 0, 0, 0}};
  setScale(&number_1, 1);
  s21_truncate(number_1, &number_1);
  ck_assert_int_eq(s21_is_equal(number_1, check), 1);
}

END_TEST

START_TEST(s21_truncate_test4) {
  s21_decimal number_1 = {{123456, 0, 0, 0}};
  setScale(&number_1, 3);
  setSign(&number_1, 1);
  s21_decimal check = {{123, 0, 0, 0}};
  setSign(&check, 1);
  s21_truncate(number_1, &number_1);
  ck_assert_int_eq(s21_is_equal(number_1, check), 1);
}

END_TEST

START_TEST(s21_truncate_test5) {
  s21_decimal src1;
  src1.bits[3] = 0x000A0000;
  src1.bits[2] = 0x0;
  src1.bits[1] = 0xFFFFFFFF;
  src1.bits[0] = 0xFFFFFFFF;
  s21_decimal result;
  result.bits[3] = 0x0;
  result.bits[2] = 0x0;
  result.bits[1] = 0x0;
  result.bits[0] = 0x6DF37F67;
  s21_decimal res_od;
  s21_truncate(src1, &res_od);
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}

END_TEST

START_TEST(s21_truncate_test6) {
  s21_decimal src1;
  src1.bits[0] = 0b00000000000000000000000001101101;
  src1.bits[1] = 0b00000000000011000110010101011011;
  src1.bits[2] = 0b00000000000000000011000000111001;
  src1.bits[3] = 0b00000000000011100000000000000000;
  s21_decimal result;
  result.bits[0] = 0b10000111101111000001011000011110;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res_od;
  s21_truncate(src1, &res_od);
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}

END_TEST

START_TEST(s21_truncate_test7) {
  s21_decimal number_1 = {{5, 0, 0, 0}};
  s21_decimal check = {{0, 0, 0, 0}};
  setScale(&number_1, 1);
  s21_truncate(number_1, &number_1);
  ck_assert_int_eq(s21_is_equal(number_1, check), 1);
}

END_TEST

START_TEST(s21_truncate_test8) {
  s21_decimal number_1 = {{5, 0, 0, 0}};
  s21_decimal check = {{0, 0, 0, 0}};
  setScale(&number_1, 1);
  s21_truncate(number_1, &number_1);
  ck_assert_int_eq(s21_is_equal(number_1, check), 1);
}

END_TEST

START_TEST(s21_truncate_test9) {
  int a = 0;
  s21_decimal my_decimal_1 = {{6, 0, 0, 0}};
  s21_decimal check_number = {{0, 0, 0, 0}};
  s21_decimal otvet = {{6, 0, 0, 0}};
  int my_result = s21_truncate(my_decimal_1, &check_number);
  ck_assert_int_eq(my_result, a);
  ck_assert_int_eq(otvet.bits[3], check_number.bits[3]);
  ck_assert_int_eq(otvet.bits[2], check_number.bits[2]);
  ck_assert_int_eq(otvet.bits[1], check_number.bits[1]);
  ck_assert_int_eq(otvet.bits[0], check_number.bits[0]);
}

END_TEST

START_TEST(s21_truncate_test10) {
  int a = 0;
  s21_decimal my_decimal_1 = {{6, 0, 0, 2097152}};
  s21_decimal check_number = {{0, 0, 0, 0}};
  s21_decimal otvet = {{0, 0, 0, 0}};
  int my_result = s21_truncate(my_decimal_1, &check_number);
  ck_assert_int_eq(my_result, a);
  ck_assert_int_eq(otvet.bits[3], check_number.bits[3]);
  ck_assert_int_eq(otvet.bits[2], check_number.bits[2]);
  ck_assert_int_eq(otvet.bits[1], check_number.bits[1]);
  ck_assert_int_eq(otvet.bits[0], check_number.bits[0]);
}

END_TEST

START_TEST(s21_truncate_test11) {
  int a = 0;
  s21_decimal my_decimal_1 = {{6, 0, 12, 65536}};
  s21_decimal check_number = {{0, 0, 0, 0}};
  s21_decimal otvet = {{858993459, 858993459, 1, 0}};
  int my_result = s21_truncate(my_decimal_1, &check_number);
  ck_assert_int_eq(my_result, a);
  ck_assert_int_eq(otvet.bits[3], check_number.bits[3]);
  ck_assert_int_eq(otvet.bits[2], check_number.bits[2]);
  ck_assert_int_eq(otvet.bits[1], check_number.bits[1]);
  ck_assert_int_eq(otvet.bits[0], check_number.bits[0]);
}

END_TEST

START_TEST(s21_truncate_test12) {
  int a = 0;
  s21_decimal my_decimal_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 65536}};
  s21_decimal check_number = {{0, 0, 0, 0}};
  s21_decimal otvet = {{0x99999999, 0x99999999, 0x19999999, 0}};
  int my_result = s21_truncate(my_decimal_1, &check_number);
  ck_assert_int_eq(my_result, a);
  ck_assert_int_eq(otvet.bits[3], check_number.bits[3]);
  ck_assert_int_eq(otvet.bits[2], check_number.bits[2]);
  ck_assert_int_eq(otvet.bits[1], check_number.bits[1]);
  ck_assert_int_eq(otvet.bits[0], check_number.bits[0]);
}

END_TEST

START_TEST(s21_truncate_test13) {
  s21_decimal input = {{0, 0, 0, 0}};
  setScale(&input, 15);
  s21_decimal expected = {{0}};
  s21_decimal result;
  s21_truncate(input, &result);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

START_TEST(s21_truncate_test14) {
  s21_decimal input = {{362732873, 0, 0, 0}};
  setSign(&input, 1);
  s21_decimal expected = {{362732873, 0, 0, 0}};
  setSign(&expected, 1);
  s21_decimal result;
  s21_truncate(input, &result);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

START_TEST(s21_truncate_test15) {
  s21_decimal input = {{572963473, 0, 0, 0}};
  setScale(&input, 4);
  s21_decimal expected = {{57296, 0, 0, 0}};
  s21_decimal result;
  s21_truncate(input, &result);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

START_TEST(s21_truncate_test16) {
  s21_decimal input = {{0xb54ac285, 0x9bde85, 0, 0}};
  setScale(&input, 8);
  setSign(&input, 1);
  s21_decimal expected = {{0x1a268848, 0, 0, 0}};
  setSign(&expected, 1);
  s21_decimal result;
  s21_truncate(input, &result);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

START_TEST(s21_truncate_test17) {
  s21_decimal input = {{0x4C577A00, 0xC0D845D, 0, 0}};
  setScale(&input, 8);
  s21_decimal expected = {{0x5A9F2BA, 0x2, 0, 0}};
  s21_decimal result;
  s21_truncate(input, &result);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

START_TEST(s21_truncate_test18) {
  s21_decimal input = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  setScale(&input, 28);
  setSign(&input, 1);
  s21_decimal expected = {{7, 0, 0, 0}};
  setSign(&expected, 1);
  s21_decimal result;
  s21_truncate(input, &result);
  ASSERT_DECIMAL_EQ(result, expected)
}

END_TEST

Suite *truncate_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("truncate");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_truncate_test1);
  tcase_add_test(tc_core, s21_truncate_test2);
  tcase_add_test(tc_core, s21_truncate_test3);
  tcase_add_test(tc_core, s21_truncate_test4);
  tcase_add_test(tc_core, s21_truncate_test5);
  tcase_add_test(tc_core, s21_truncate_test6);
  tcase_add_test(tc_core, s21_truncate_test7);
  tcase_add_test(tc_core, s21_truncate_test8);
  tcase_add_test(tc_core, s21_truncate_test9);
  tcase_add_test(tc_core, s21_truncate_test10);
  tcase_add_test(tc_core, s21_truncate_test11);
  tcase_add_test(tc_core, s21_truncate_test12);
  tcase_add_test(tc_core, s21_truncate_test13);
  tcase_add_test(tc_core, s21_truncate_test14);
  tcase_add_test(tc_core, s21_truncate_test15);
  tcase_add_test(tc_core, s21_truncate_test16);
  tcase_add_test(tc_core, s21_truncate_test17);
  tcase_add_test(tc_core, s21_truncate_test18);
  suite_add_tcase(s, tc_core);
  return s;
}
