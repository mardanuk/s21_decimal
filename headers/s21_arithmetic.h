#include "s21_common.h"
#include "s21_structs.h"

#ifndef S21_ARITHMETIC_H_
#define S21_ARITHMETIC_H_

int s21_add(s21_decimal number1, s21_decimal number2, s21_decimal *result);

int s21_sub(s21_decimal number1, s21_decimal number2, s21_decimal *result);

int s21_mul(s21_decimal number1, s21_decimal number2, s21_decimal *result);

int s21_div(s21_decimal number1, s21_decimal number2, s21_decimal *result);

int s21_negate(s21_decimal number, s21_decimal *result);

#endif