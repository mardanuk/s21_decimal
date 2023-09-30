#include "../../headers/s21_arithmetic.h"
#include "../../headers/s21_conversion.h"

void deleteTrailingZerosInUnsigned(unsigned int *mantissa) {
  int index = 0;
  while (getBitUnsigned(mantissa, 0) == 0) {
    (*mantissa) >>= 1;
    index++;
  }
}

void deleteTrailingZerosInDecimal(s21_decimal *number) {
  s21_decimal res = {0};
  s21_decimal remainder = {0};
  baseDivision(number, (s21_decimal *)&DECIMAL_TEN, &res, &remainder);
  int scale = getScale(number);
  while (remainder.bits[0] == S21_ZERO_VALUE && scale-- > S21_ZERO_SCALE) {
    copyMantissa(number, &res);
    baseDivision(number, (s21_decimal *)&DECIMAL_TEN, &res, &remainder);
  }
  setScale(number, scale);
}

void adjustDecimalForFloatConversion(s21_decimal *dest) {
  s21_decimal res = {0};
  s21_decimal remainder = {0};
  s21_decimal destCopy = *dest;
  int count = getCountDigitsInDecimalMantissa(*dest), scale = getScale(dest);
  int countNumsToReduce = count - SAVING_NUMBERS_IN_FLOAT;

  for (int i = 0; i < countNumsToReduce; i++) {
    baseDivision(&destCopy, (s21_decimal *)&DECIMAL_TEN, &res, &remainder);
    copyMantissa(&destCopy, &res);
    scale--;
  }

  if (remainder.bits[firstBit] >= S21_BOUND_VALUE_TO_ROUND)
    baseAddition(&destCopy, (s21_decimal *)&DECIMAL_ONE, &destCopy);

  while (scale < S21_ZERO_SCALE &&
         count != getCountDigitsInDecimalMantissa(destCopy)) {
    baseMultiply(&destCopy, (s21_decimal *)&DECIMAL_TEN, &res);
    copyMantissa(&destCopy, &res);
    scale++;
    setScale(&destCopy, scale);
  }

  copyNumber(dest, &destCopy);
  setScale(dest, scale);
}

int getScaleFloatNumber(unsigned bits) {
  return (int)((bits << SIGN_BIT_NUMBER) >> MANTISSA_START_BIT_NUMBER) -
         FLOAT_EXP_MAX;
}

unsigned getMantissaFloatNumber(unsigned bits) {
  return (bits << EXP_START_BIT_NUMBER) >> EXP_START_BIT_NUMBER;
}

unsigned changeBinaryRepresentationFromFloatToUnsigned(float number) {
  union floatUnsignedUnion converter;
  converter.floatValue = number;
  return converter.unsignedValue;
}

int isZeroInput(float src) { return src == S21_ZERO_FLOAT; }

void handleScaleForFloatNumber(int scale, s21_decimal mantissaDecimal,
                               s21_decimal expDecimal, s21_decimal *dest) {
  if (scale < S21_ZERO_SCALE)
    s21_div(mantissaDecimal, expDecimal, dest);
  else
    s21_mul(mantissaDecimal, expDecimal, dest);
}

float getSingFloat(s21_decimal src) {
  return getSign(&src) ? S21_NEGATIVE_ONE_FLOAT : S21_POSITIVE_ONE_FLOAT;
}

int handleInitialErrorConditionFromDecimalToFloat(s21_decimal src,
                                                  float *dest) {
  int errorCode = errorCodeConversion_noError;
  int scale = getScale(&src);
  if (dest == NULL) {
    errorCode = errorCodeConversion_conversionError;
  } else if (scale > S21_MAX_AVAILABLE_SCALE_VALUE) {
    *dest = 0;
    errorCode = errorCodeConversion_conversionError;
  }
  return errorCode;
}
