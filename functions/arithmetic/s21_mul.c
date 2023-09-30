#include "../../headers/s21_arithmetic.h"

int s21_mul(s21_decimal number1, s21_decimal number2, s21_decimal *result) {
  s21_big_decimal number1_big = {0}, number2_big = {0}, result_big = {0};

  number1_big = fromDecimalToBigDecimal(&number1);
  number2_big = fromDecimalToBigDecimal(&number2);

  baseMultiplication_big(&number1_big, &number2_big, &result_big);

  int overflowScale = normalizeFromBigDecimalToDecimal(result, &result_big);
  int resultSign = getSign(&number1) ^ getSign(&number2);

  setSign(result, resultSign);
  int errorCode = handleScaleOverflowMultiplication(&number1, &number2, result,
                                                    overflowScale);
  if (errorCode) {
    clearDecimalNumber(result);
    if (resultSign)
      errorCode = errorCodeArithmetic_tooSmallOrNegativeInfinity;
    else
      errorCode = errorCodeArithmetic_tooLargeOrInfinity;
  }
  return errorCode;
}
