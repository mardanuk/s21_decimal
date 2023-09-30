#include "../../headers/s21_common.h"

int getCountDigitsInDecimalMantissa(s21_decimal dest) {
  int count = 0;
  s21_decimal res = {0};
  s21_decimal remainder = {0};
  while (!isZero(&dest)) {
    baseDivision(&dest, (s21_decimal *)&DECIMAL_TEN, &res, &remainder);
    copyNumber(&dest, &res);
    count++;
  }
  return count;
}

int getIndexHighestBitUnsigned(unsigned int *number) {
  int result = 0;
  for (int i = S21_SIZEOF_INT_BIT - 1; i >= 0 && !result; i--)
    result = getBitUnsigned(number, i) ? i : 0;
  return result;
}

void performComparison(s21_decimal *number1, s21_decimal *number2,
                       int *pReturnValue) {
  int sign1 = getSign(number1);
  int sign2 = getSign(number2);
  int isEqualSign = sign1 == sign2;
  for (int i = thirdBit; isEqualSign && i >= firstBit &&
                         *pReturnValue == compareReturnValue_equal;
       i--) {
    if (number1->bits[i] < number2->bits[i]) {
      *pReturnValue =
          sign1 == 0 ? compareReturnValue_lower : compareReturnValue_greater;
    } else if (number1->bits[i] > number2->bits[i]) {
      *pReturnValue =
          sign1 == 0 ? compareReturnValue_greater : compareReturnValue_lower;
    }
  }
}

int compareNumbers(s21_decimal *number1, s21_decimal *number2) {
  int returnValue = compareReturnValue_equal;
  if (!isZero(number1) || !isZero(number2)) {
    int sign1 = getSign(number1);
    int sign2 = getSign(number2);
    if (sign1 != sign2)
      returnValue =
          sign1 == 0 ? compareReturnValue_greater : compareReturnValue_lower;
    performComparison(number1, number2, &returnValue);
  }
  return returnValue;
}

int isEqual(s21_decimal *number1, s21_decimal *number2) {
  return compareNumbers(number1, number2) == compareReturnValue_equal;
}

int isLower(s21_decimal *number1, s21_decimal *number2) {
  return compareNumbers(number1, number2) == compareReturnValue_lower;
}

int isGreater(s21_decimal *number1, s21_decimal *number2) {
  return compareNumbers(number1, number2) == compareReturnValue_greater;
}

int isZero(s21_decimal *number) {
  return (number->bits[firstBit] == 0 && number->bits[secondBit] == 0 &&
          number->bits[thirdBit] == 0);
}

void copyNumber(s21_decimal *numberDest, s21_decimal *numberSrc) {
  for (int i = 0; i < S21_DECIMAL_INT_BITS_COUNT; ++i) {
    numberDest->bits[i] = numberSrc->bits[i];
  }
}

void copyMantissa(s21_decimal *numberDest, s21_decimal *numberSrc) {
  for (int i = 0; i < S21_DECIMAL_MANTISSA_INT_BITS_COUNT; ++i) {
    numberDest->bits[i] = numberSrc->bits[i];
  }
}

void twosComplementNegate(s21_decimal *number) {
  for (int i = 0; i < S21_MANTISSA_SIZE; i++)
    setBitMantissa(number, i, reverseBit(getBitMantissa(number, i)));
  s21_decimal result = {0};
  baseAddition(number, (s21_decimal *)&DECIMAL_ONE, &result);
  setSign(&result, 1);
  setScale(&result, getScale(number));
  copyNumber(number, &result);
}

void handleZeroValues(s21_decimal *number1, s21_decimal *number2) {
  handleZeroValue(number1);
  handleZeroValue(number2);
}

void handleZeroValue(s21_decimal *number) {
  if (isZero(number)) {
    setScale(number, S21_ZERO_SCALE);
  }
}

void handleSignOverflow(unsigned carry, s21_decimal *number) {
  if (carry && getSign(number)) setSign(number, 0);
}

void handleNegativeNumber(s21_decimal *number) {
  if (getSign(number) == 1) twosComplementNegate(number);
}

int handleNegativeNumbers(s21_decimal *number1, s21_decimal *number2) {
  int isEqualSign = (getSign(number1) == getSign(number2));
  if (!isEqualSign) {
    handleNegativeNumber(number1);
    handleNegativeNumber(number2);
  }
  return isEqualSign;
}

int handleReturnValueAdd(s21_decimal *number, int carry, int isEqualSign) {
  int errorCode = errorCodeArithmetic_noError;
  if (isEqualSign && carry) {
    if (getSign(number))
      errorCode = errorCodeArithmetic_tooSmallOrNegativeInfinity;
    else
      errorCode = errorCodeArithmetic_tooLargeOrInfinity;
  }
  return errorCode;
}

int handleExtraOneAtTheEndOfDividing(s21_decimal *divider,
                                     s21_decimal *remainder,
                                     s21_decimal *result) {
  int scale = getScale(result);
  s21_decimal multiplyResult = {0};
  s21_decimal divisionResult = {0}, divisionRemainder = {0};
  baseMultiply(remainder, (s21_decimal *)&DECIMAL_TEN, &multiplyResult);
  baseDivision(&multiplyResult, divider, &divisionResult, &divisionRemainder);
  if (divisionResult.bits[0] >= S21_BOUND_VALUE_TO_ROUND) {
    s21_decimal additionResult = {0};
    baseAddition(result, (s21_decimal *)&DECIMAL_ONE, &additionResult);
    copyNumber(result, &additionResult);
    setScale(result, scale);
  }
  return 0;
}

int handleNonZeroRemainder(s21_decimal *divisor, s21_decimal *result,
                           s21_decimal *remainder, int *pResultScale) {
  int multiplicationErrorCode = errorCode_noError;
  s21_decimal tempRemainder = {0};
  copyNumber(&tempRemainder, remainder);
  while (!isZero(&tempRemainder) &&
         *pResultScale < S21_MAX_AVAILABLE_SCALE_VALUE &&
         !multiplicationErrorCode) {
    s21_decimal tempRemainderCopy = {0}, tempResultCopy = {0};
    s21_decimal divisionResult = {0};
    s21_decimal divisionRemainder = {0};

    baseMultiply(&tempRemainder, (s21_decimal *)&DECIMAL_TEN,
                 &tempRemainderCopy);

    baseDivision(&tempRemainderCopy, divisor, &divisionResult,
                 &divisionRemainder);

    multiplicationErrorCode =
        baseMultiply(result, (s21_decimal *)&DECIMAL_TEN, &tempResultCopy);

    if (!multiplicationErrorCode) {
      copyNumber(result, &tempResultCopy);
      if (!isZero(&divisionResult)) {
        s21_decimal additionResult = {0};
        baseAddition(result, &divisionResult, &additionResult);
        copyNumber(result, &additionResult);
      }
      (*pResultScale)++;
      copyNumber(&tempRemainder, &divisionRemainder);
    }
    copyNumber(remainder, &divisionRemainder);
  }
  return errorCode_noError;
}

int handleReturnValue_mul(s21_decimal *number1, s21_decimal *number2) {
  int errorCode = errorCodeArithmetic_noError;
  int highestBit1 = getIndexHighestBitMantissa(number1);
  int highestBit2 = getIndexHighestBitMantissa(number2);
  int highestBitSum = highestBit1 + highestBit2;
  if (highestBitSum >= S21_MANTISSA_HIGHEST_BIT) {
    int sign = getSign(number1) ^ getSign(number2);
    if (sign)
      errorCode = errorCodeArithmetic_tooSmallOrNegativeInfinity;
    else
      errorCode = errorCodeArithmetic_tooLargeOrInfinity;
  }
  return errorCode;
}

int handleNegativeScaleForDivision(s21_decimal *result, int *pResultScale) {
  if (*pResultScale > S21_ZERO_SCALE) return errorCode_noError;
  int multiplyError = errorCode_noError;
  for (; !multiplyError && *pResultScale < S21_ZERO_SCALE;) {
    s21_decimal multiplyResult = {0};
    multiplyError =
        baseMultiply(result, (s21_decimal *)&DECIMAL_TEN, &multiplyResult);
    if (!multiplyError) {
      (*pResultScale)++;
      copyNumber(result, &multiplyResult);
    }
  }
  return multiplyError;
}

int scaleUp(s21_decimal *number, int scaleDifference) {
  int errorCode = errorCode_noError;
  for (int i = 0; i < scaleDifference && !errorCode; i++) {
    s21_decimal tempResult = {0};
    errorCode = baseMultiply(number, (s21_decimal *)&DECIMAL_TEN, &tempResult);
    if (!errorCode) {
      setScale(&tempResult, getScale(number) + 1);
      copyNumber(number, &tempResult);
    }
  }
  return errorCode;
}

s21_decimal scaleDown(s21_decimal *number, int scaleDifference) {
  s21_decimal remainder = {0};
  for (int i = 0; i < scaleDifference; i++) {
    s21_decimal tempResult = {0};
    baseDivision(number, (s21_decimal *)&DECIMAL_TEN, &tempResult, &remainder);
    setSign(&tempResult, getSign(number));
    setScale(&tempResult, getScale(number) - 1);
    copyNumber(number, &tempResult);
  }
  return remainder;
}

int handleScaleUp(s21_decimal *number1, s21_decimal *number2) {
  int scale1 = getScale(number1);
  int scale2 = getScale(number2);
  int errorCode = !(scale1 < S21_MAX_AVAILABLE_SCALE_VALUE &&
                    scale2 < S21_MAX_AVAILABLE_SCALE_VALUE);
  int scaleDifference = scale1 - scale2;
  if (!errorCode && scaleDifference > S21_ZERO_SCALE) {
    errorCode = scaleUp(number2, scaleDifference);
  } else if (!errorCode && scaleDifference < S21_ZERO_SCALE) {
    errorCode = scaleUp(number1, scaleDifference * (-1));
  }
  return errorCode;
}

void handleScaleDown(s21_decimal *number1, s21_decimal *number2) {
  int scale1 = getScale(number1);
  int scale2 = getScale(number2);
  int scaleDifference = scale1 - scale2;
  s21_decimal remainder;
  if (scaleDifference > 0) {
    remainder = scaleDown(number1, scaleDifference);
    handleExtraOneAtTheEndOfDividing((s21_decimal *)&DECIMAL_TEN, &remainder,
                                     number1);
  } else if (scaleDifference < 0) {
    remainder = scaleDown(number2, scaleDifference * (-1));
    handleExtraOneAtTheEndOfDividing((s21_decimal *)&DECIMAL_TEN, &remainder,
                                     number2);
  }
}

void normalize(s21_decimal *number1, s21_decimal *number2) {
  int sign1 = getSign(number1);
  int sign2 = getSign(number2);
  setSign(number1, 0);
  setSign(number2, 0);

  int errorCode = handleScaleUp(number1, number2);
  if (errorCode) handleScaleDown(number1, number2);

  setSign(number1, sign1);
  setSign(number2, sign2);
}

int baseAddition(s21_decimal *number1, s21_decimal *number2,
                 s21_decimal *result) {
  int carry = 0;
  for (int i = 0; i < S21_MANTISSA_SIZE; i++) {
    int bit1 = getBitMantissa(number1, i);
    int bit2 = getBitMantissa(number2, i);
    int sum = bit1 + bit2 + carry;
    carry = (bit1 & bit2) | ((bit1 | bit2) & carry);
    setBitMantissa(result, i, sum & 1);
  }
  return carry != 0;
}

int baseAdditionShell(s21_decimal number1, s21_decimal number2,
                      s21_decimal *result) {
  handleZeroValues(&number1, &number2);

  int isEqualSign = handleNegativeNumbers(&number1, &number2);

  int carry = baseAddition(&number1, &number2, result);

  if (!isEqualSign) setSign(result, 1);
  handleSignOverflow(carry, result);
  if (getSign(result) || !isEqualSign) handleNegativeNumber(result);
  setSign(result, isEqualSign ? getSign(&number1) : getSign(result));
  setScale(result, getScale(&number1));
  handleZeroValue(result);
  int errorCode = handleReturnValueAdd(&number1, carry, isEqualSign);

  if (errorCode) clearDecimalNumber(result);
  return errorCode;
}

int baseSubtraction(s21_decimal number1, s21_decimal number2,
                    s21_decimal *result) {
  setSign(&number2, reverseBit(getSign(&number2)));
  return baseAdditionShell(number1, number2, result);
}

int baseDivision(s21_decimal *number1, s21_decimal *number2,
                 s21_decimal *result, s21_decimal *remainder) {
  clearDecimalNumber(result);
  clearDecimalNumber(remainder);
  copyNumber(remainder, number1);
  int highestBit1 = getIndexHighestBitMantissa(remainder);
  int highestBit2 = getIndexHighestBitMantissa(number2);

  for (int i = highestBit1 - highestBit2; i >= 0; i--) {
    s21_decimal tmp1 = {0}, tmp2 = {0};
    copyNumber(&tmp1, number2);
    leftShift(&tmp1, i);
    if (!isGreater(&tmp1, remainder) && !isZero(&tmp1)) {
      s21_decimal tempRemainder = {0};
      baseSubtraction(*remainder, tmp1, &tempRemainder);
      copyNumber(remainder, &tempRemainder);
      copyNumber(&tmp2, (s21_decimal *)&DECIMAL_ONE);
      leftShift(&tmp2, i);
      baseAddition(result, &tmp2, result);
    }
  }
  return errorCode_noError;
}

int baseMultiply(s21_decimal *number1, s21_decimal *number2,
                 s21_decimal *result) {
  clearDecimalNumber(result);
  int errorCode = handleReturnValue_mul(number1, number2);
  for (int i = 0; i < S21_MANTISSA_SIZE && !errorCode; i++) {
    if (getBitMantissa(number2, i)) {
      s21_decimal tempResult;
      copyNumber(&tempResult, number1);
      leftShift(&tempResult, i);
      baseAddition(result, &tempResult, result);
    }
  }
  return errorCode;
}

int handleScaleOverflowMultiplication(s21_decimal *number1,
                                      s21_decimal *number2, s21_decimal *result,
                                      int overflowScale) {
  int errorCode = errorCode_noError;
  int resultScale = getScale(number1) + getScale(number2) - overflowScale;
  if (resultScale < S21_ZERO_SCALE)
    errorCode = errorCode_numberIsTooSmallOrGreat;
  if (!errorCode) {
    setScale(result, resultScale);
    if (resultScale > S21_MAX_AVAILABLE_SCALE_VALUE) {
      s21_decimal resultWithMaxScale;
      copyNumber(&resultWithMaxScale, result);
      setScale(&resultWithMaxScale, S21_MAX_AVAILABLE_SCALE_VALUE);
      normalize(result, &resultWithMaxScale);
    }
  }
  return errorCode;
}

int normalizeFromBigDecimalToDecimal(s21_decimal *dest, s21_big_decimal *src) {
  s21_big_decimal tempResult = {0};
  s21_big_decimal remainder = {0};
  int overflowScale = S21_ZERO_SCALE;
  while (isBigDecimal(src)) {
    baseDivision_big(src, (s21_big_decimal *)&BIG_DECIMAL_TEN, &tempResult,
                     &remainder);
    copyNumber_big(src, &tempResult);
    overflowScale++;
  }
  fromBigDecimalToDecimal(dest, src);
  return overflowScale;
}

s21_decimal baseMod(s21_decimal *dividend, s21_decimal *divider) {
  s21_decimal result = {0}, remainder = {0};
  baseDivision(dividend, divider, &result, &remainder);
  return remainder;
}

void handleExcessScale(s21_decimal *number) {
  int power = getScale(number);
  if (power) {
    setSign(number, 0);
    s21_decimal modResult = baseMod(number, (s21_decimal *)&DECIMAL_TEN);
    if (isZero(&modResult)) scaleDown(number, 1);
  }
}

void handleErrorCodeDivision(s21_decimal *result, int *pErrorCode,
                             int resultScale, int resultSign) {
  if (resultScale < S21_ZERO_SCALE || *pErrorCode) {
    clearDecimalNumber(result);
    if (resultSign)
      *pErrorCode = errorCodeArithmetic_tooSmallOrNegativeInfinity;
    else
      *pErrorCode = errorCodeArithmetic_tooLargeOrInfinity;
  }
}

int handleInitialErrorConditionDivision(s21_decimal *number1,
                                        s21_decimal *number2,
                                        s21_decimal *result) {
  int errorCode = errorCodeArithmetic_noError;
  if (isZero(number2)) errorCode = errorCodeArithmetic_divisionByZero;
  if (isZero(number1)) {
    clearDecimalNumber(result);
    errorCode = errorCodeArithmetic_noError;
  }
  return errorCode;
}

int handleInitialErrorConditionFromFloatToDecimal(float src) {
  int isSrcUndefined = (src != src || src == S21_POS_INF || src == S21_NEG_INF);
  int isSrcInTheBounds =
      (fabsf(src) >= S21_DECIMAL_EXP_MIN && fabsf(src) <= S21_DECIMAL_EXP_MAX);
  return isSrcUndefined || !isSrcInTheBounds;
}