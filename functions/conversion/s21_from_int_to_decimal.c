#include "../../headers/s21_conversion.h"

int s21_from_int_to_decimal(int src, s21_decimal *dest) {
  clearDecimalNumber(dest);
  int sign = src < S21_ZERO_VALUE;
  dest->bits[firstBit] = sign ? -src : src;
  setSign(dest, sign);
  return errorCodeConversion_noError;
}
