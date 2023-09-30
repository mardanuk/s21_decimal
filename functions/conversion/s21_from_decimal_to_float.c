#include "../../headers/s21_conversion.h"

int s21_from_decimal_to_float(s21_decimal src, float *dest) {
  int errorCode = handleInitialErrorConditionFromDecimalToFloat(src, dest);
  if (errorCode) return errorCodeConversion_conversionError;

  int scale = getScale(&src);
  float sign = getSingFloat(src);

  double tempDest = 0;

  for (int i = 0; i < getIndexHighestBitMantissa(&src) + 1; i++)
    tempDest += pow(2, i) * getBitMantissa(&src, i);

  if (scale != 0) tempDest /= pow(10, scale);
  *dest = (float)(tempDest)*sign;
  return errorCode;
}
