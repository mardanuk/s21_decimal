#include "../../headers/s21_overloads.h"

#include "../../headers/s21_common.h"

int baseMultiplication_big(s21_big_decimal *number1, s21_big_decimal *number2,
                           s21_big_decimal *result) {
  clearDecimalNumber_big(result);
  int errorCode = handleReturnValueMul_big(number1, number2);
  for (int i = 0; i < S21_BIG_MANTISSA_SIZE && !errorCode; i++) {
    if (getBitMantissa_big(number2, i)) {
      s21_big_decimal tempResult = {0};
      copyNumber_big(&tempResult, number1);
      leftShift_big(&tempResult, i);
      baseAddition_big(result, &tempResult, result);
    }
  }
  return errorCode;
}

int baseDivision_big(s21_big_decimal *number1, s21_big_decimal *number2,
                     s21_big_decimal *result, s21_big_decimal *remainder) {
  clearDecimalNumber_big(result);
  copyNumber_big(remainder, number1);
  int highestBit1 = getIndexHighestBitMantissa_big(remainder);
  int highestBit2 = getIndexHighestBitMantissa_big(number2);
  for (int i = highestBit1 - highestBit2; i >= 0; i--) {
    s21_big_decimal tmp1 = {0}, tmp2 = {0};
    copyNumber_big(&tmp1, number2);
    leftShift_big(&tmp1, i);
    if ((!isGreater_big(&tmp1, remainder) && !isZero_big(&tmp1))) {
      s21_big_decimal tempRemainder = {0};
      baseSubtraction_big(*remainder, tmp1, &tempRemainder);
      copyNumber_big(remainder, &tempRemainder);
      copyNumber_big(&tmp2, (s21_big_decimal *)&BIG_DECIMAL_ONE);
      leftShift_big(&tmp2, i);
      baseAddition_big(result, &tmp2, result);
    }
  }
  return errorCode_noError;
}

int baseAdditionShell_big(s21_big_decimal number1, s21_big_decimal number2,
                          s21_big_decimal *result) {
  handleZeroValues_big(&number1, &number2);
  int isEqualSign = handleNegativeNumbers_big(&number1, &number2);
  unsigned carry = baseAddition_big(&number1, &number2, result);
  if (!isEqualSign) setSign_big(result, 1);
  handleZeroValue_big(result);
  handleSignOverflow_big(carry, result);
  if (getSign_big(result) || !isEqualSign) handleNegativeNumber_big(result);
  setSign_big(result,
              isEqualSign ? getSign_big(&number1) : getSign_big(result));
  setScale_big(result, getScale_big(&number1));
  int errorCode = handleReturnValueAdd_big(&number1, carry, isEqualSign);
  if (errorCode) clearDecimalNumber_big(result);
  return errorCode;
}

int baseSubtraction_big(s21_big_decimal number1, s21_big_decimal number2,
                        s21_big_decimal *result) {
  setSign_big(&number2, reverseBit(getSign_big(&number2)));
  return baseAdditionShell_big(number1, number2, result);
}

unsigned baseAddition_big(s21_big_decimal *number1, s21_big_decimal *number2,
                          s21_big_decimal *result) {
  unsigned int carry = 0;
  for (int i = 0; i < S21_BIG_MANTISSA_SIZE; i++) {
    unsigned int bit1 = getBitMantissa_big(number1, i);
    unsigned int bit2 = getBitMantissa_big(number2, i);
    unsigned int sum = bit1 + bit2 + carry;
    carry = (bit1 & bit2) | ((bit1 | bit2) & carry);
    setBitMantissa_big(result, i, (int)sum & 1);
  }
  return carry;
}

int handleReturnValueMul_big(s21_big_decimal *number1,
                             s21_big_decimal *number2) {
  int errorCode = errorCodeArithmetic_noError;
  int highestBit1 = getIndexHighestBitMantissa_big(number1);
  int highestBit2 = getIndexHighestBitMantissa_big(number2);
  int highestBitSum = highestBit1 + highestBit2;
  if (highestBitSum >= S21_BIG_MANTISSA_SIZE) {
    int sign = getSign_big(number1) ^ getSign_big(number2);
    if (sign)
      errorCode = errorCodeArithmetic_tooSmallOrNegativeInfinity;
    else
      errorCode = errorCodeArithmetic_tooLargeOrInfinity;
  }
  return (int)errorCode;
}

int handleReturnValueAdd_big(s21_big_decimal *number, unsigned carry,
                             int isEqualSign) {
  int errorCode = errorCodeArithmetic_noError;
  if (isEqualSign && carry) {
    if (getSign_big(number))
      errorCode = errorCodeArithmetic_tooSmallOrNegativeInfinity;
    else
      errorCode = errorCodeArithmetic_tooLargeOrInfinity;
  }
  return errorCode;
}

int handleNegativeNumbers_big(s21_big_decimal *number1,
                              s21_big_decimal *number2) {
  int isEqualSign = (getSign_big(number1) == getSign_big(number2));
  if (!isEqualSign) {
    handleNegativeNumber_big(number1);
    handleNegativeNumber_big(number2);
  }
  return isEqualSign;
}

void handleNegativeNumber_big(s21_big_decimal *number) {
  if (getSign_big(number) == 1) twosComplementNegate_big(number);
}

void handleSignOverflow_big(unsigned carry, s21_big_decimal *number) {
  if (carry && getSign_big(number)) setSign_big(number, 0);
}

void handleZeroValue_big(s21_big_decimal *number) {
  if (isZero_big(number)) {
    setSign_big(number, 0);
    setScale_big(number, 0);
  }
}

void handleZeroValues_big(s21_big_decimal *number1, s21_big_decimal *number2) {
  handleZeroValue_big(number1);
  handleZeroValue_big(number2);
}
void twosComplementNegate_big(s21_big_decimal *number) {
  for (int i = 0; i < S21_BIG_MANTISSA_SIZE; i++)
    setBitMantissa_big(number, i, reverseBit(getBitMantissa_big(number, i)));
  s21_big_decimal result = {0};
  baseAddition_big(number, (s21_big_decimal *)&BIG_DECIMAL_ONE, &result);
  setSign_big(&result, 1);
  setScale_big(&result, getScale_big(number));
  copyNumber_big(number, &result);
}

int isZero_big(s21_big_decimal *number) {
  return (number->bits[firstBit_big] == 0 && number->bits[secondBit_big] == 0 &&
          number->bits[thirdBit_big] == 0 && number->bits[fourthBit_big] == 0 &&
          number->bits[fifthBit_big] == 0 && number->bits[sixthBit_big] == 0 &&
          number->bits[seventhBit_big] == 0);
}

int isGreater_big(const s21_big_decimal *number1,
                  const s21_big_decimal *number2) {
  return compareNumbers_big(number1, number2) == 1;
}

int compareNumbers_big(const s21_big_decimal *number1,
                       const s21_big_decimal *number2) {
  int result = compareReturnValue_equal;
  for (int i = 6; i >= 0 && result == compareReturnValue_equal; i--) {
    if (number1->bits[i] < number2->bits[i]) {
      result = compareReturnValue_lower;
    } else if (number1->bits[i] > number2->bits[i]) {
      result = compareReturnValue_greater;
    }
  }
  return result;
}
