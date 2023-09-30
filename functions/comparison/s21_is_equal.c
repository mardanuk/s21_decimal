#include "../../headers/s21_comparison.h"

int s21_is_equal(s21_decimal number1, s21_decimal number2) {
  normalize(&number1, &number2);
  return isEqual(&number1, &number2);
}
