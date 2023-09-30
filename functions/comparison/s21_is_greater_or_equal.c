#include "../../headers/s21_comparison.h"

int s21_is_greater_or_equal(s21_decimal number1, s21_decimal number2) {
  return s21_is_greater(number1, number2) || s21_is_equal(number1, number2);
}
