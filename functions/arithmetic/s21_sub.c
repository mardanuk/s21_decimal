#include "../../headers/s21_arithmetic.h"

int s21_sub(s21_decimal number1, s21_decimal number2, s21_decimal *result) {
  setSign(&number2, reverseBit(getSign(&number2)));
  return s21_add(number1, number2, result);
}