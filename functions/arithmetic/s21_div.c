#include "../../headers/s21_arithmetic.h"

int s21_div(s21_decimal number1, s21_decimal number2, s21_decimal *result) {
  int errorCode =
      handleInitialErrorConditionDivision(&number1, &number2, result);
  if (errorCode) return errorCode;

  s21_decimal remainder = {0};

  int resultSign = getSign(&number1) ^ getSign(&number2);
  int resultScale = getScale(&number1) - getScale(&number2);

  setSign(&number1, 0);
  setSign(&number2, 0);

  baseDivision(&number1, &number2, result, &remainder);

  handleNonZeroRemainder(&number2, result, &remainder, &resultScale);
  handleExtraOneAtTheEndOfDividing(&number2, &remainder, result);

  errorCode |= handleNegativeScaleForDivision(result, &resultScale);

  setScale(result, resultScale);

  handleExcessScale(result);

  handleZeroValue(result);

  setSign(result, resultSign);

  handleErrorCodeDivision(result, &errorCode, resultScale, resultSign);

  return errorCode;
}