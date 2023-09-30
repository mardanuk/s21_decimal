#include "../../headers/s21_arithmetic.h"

int s21_add(s21_decimal number1, s21_decimal number2, s21_decimal *result) {
  normalize(&number1, &number2);
  return baseAdditionShell(number1, number2, result);
}