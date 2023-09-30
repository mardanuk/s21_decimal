#include "../../headers/s21_rounding.h"

int rounding(s21_decimal number, s21_decimal *result, roundingType type) {
  s21_decimal remainder = {0}, remainderSum = {0};

  int sign = getSign(&number), carry = 0;

  setSign(&number, 0);

  while (getScale(&number) != 0) {
    remainder = scaleDown(&number, 1);
    baseAddition(&remainderSum, &remainder, &remainderSum);
  }

  copyNumber(result, &number);

  if ((type == roundingType_floor && remainderSum.bits[0] != S21_ZERO_VALUE &&
       sign == 1) ||
      (type == roundingType_round &&
       remainder.bits[0] >= S21_BOUND_VALUE_TO_ROUND))
    carry = baseAddition(&number, (s21_decimal *)&DECIMAL_ONE, result);

  setSign(result, sign);

  int errorCode =
      handleReturnValueAdd(&number, carry, 1) != errorCodeArithmetic_noError;
  if (errorCode) clearDecimalNumber(result);

  return errorCode;
}
