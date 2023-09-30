#include "../../headers/s21_arithmetic.h"
#include "../../headers/s21_conversion.h"

int s21_from_float_to_decimal(float src, s21_decimal *dest) {
  clearDecimalNumber(dest);
  int isInvalidInput = handleInitialErrorConditionFromFloatToDecimal(src);
  if (isInvalidInput) return errorCodeConversion_conversionError;
  if (isZeroInput(src)) return errorCodeConversion_noError;

  unsigned bits = changeBinaryRepresentationFromFloatToUnsigned(src);

  int scale = getScaleFloatNumber(bits);
  unsigned mantissa = getMantissaFloatNumber(bits);

  SET_BIT(mantissa, FIRST_BIT_NUMBER_IN_MANTISSA);
  deleteTrailingZerosInUnsigned(&mantissa);
  scale -= getIndexHighestBitUnsigned(&mantissa);

  s21_decimal mantissaDecimal = {{mantissa, 0, 0, 0}};
  s21_decimal expDecimal = S21_DECIMAL_ONE_LITERAL;
  leftShift(&expDecimal, abs(scale));

  handleScaleForFloatNumber(scale, mantissaDecimal, expDecimal, dest);

  int sign = src < S21_ZERO_FLOAT;
  adjustDecimalForFloatConversion(dest);
  deleteTrailingZerosInDecimal(dest);
  setSign(dest, sign);

  return errorCodeConversion_noError;
}