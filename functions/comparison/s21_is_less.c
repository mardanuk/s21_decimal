#include "../../headers/s21_comparison.h"

int s21_is_less(s21_decimal number1, s21_decimal number2) {
  normalize(&number1, &number2);
  return isLower(&number1, &number2);
}
