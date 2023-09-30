#include "../../headers/s21_arithmetic.h"

int s21_negate(s21_decimal number, s21_decimal *result) {
  setSign(&number, reverseBit(getSign(&number)));
  copyNumber(result, &number);
  return 0;
}
