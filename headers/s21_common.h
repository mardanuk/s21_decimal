#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "s21_overloads.h"
#include "s21_structs.h"

#ifndef S21_COMMON_DECIMAL_H_
#define S21_COMMON_DECIMAL_H_

#define S21_BITMASK_FOR_EXPONENT_BITS 0xFF
#define S21_BITMASK_TO_CLEAR_EXPONENT_BITS 0xFF00FFFF

#define SET_BIT(NUMBER, INDEX) (NUMBER |= (1 << INDEX))
#define RESET_BIT(NUMBER, INDEX) (NUMBER &= ~(1 << INDEX))

#define S21_BIT_IN_BYTE 8
#define S21_SIZEOF_INT_BIT ((int)(sizeof(int) * S21_BIT_IN_BYTE))
#define S21_MANTISSA_SIZE (S21_SIZEOF_INT_BIT * 3)
#define S21_MANTISSA_HIGHEST_BIT (S21_MANTISSA_SIZE - 1)
#define S21_SIGN_BIT_INDEX 127
#define S21_SIGN_BIT_INDEX_BIG 255
#define S21_DECIMAL_INT_BITS_COUNT 4
#define S21_BIG_DECIMAL_INT_BITS_COUNT 8
#define S21_DECIMAL_MANTISSA_INT_BITS_COUNT 3
#define S21_MAX_AVAILABLE_SCALE_VALUE 28
#define S21_ZERO_SCALE 0
#define S21_ZERO_FLOAT (0.0f)

#define S21_NEGATIVE_ONE_FLOAT (-1.f)
#define S21_POSITIVE_ONE_FLOAT (1.f)

#define S21_DECIMAL_EXP_MIN 1.0e-28
#define S21_DECIMAL_EXP_MAX 7.922816e+28
#define S21_POS_INF (1.0 / +0.0)
#define S21_NEG_INF (1.0 / -0.0)
#define S21_BOUND_VALUE_TO_ROUND 5
#define S21_ZERO_VALUE 0
#define S21_DECIMAL_ONE_LITERAL \
  {                             \
    { 1, 0, 0, 0 }              \
  }
#define S21_DECIMAL_TEN_LITERAL \
  {                             \
    { 10, 0, 0, 0 }             \
  }

static const s21_decimal DECIMAL_ONE = S21_DECIMAL_ONE_LITERAL;
static const s21_decimal DECIMAL_TEN = S21_DECIMAL_TEN_LITERAL;
static const s21_big_decimal BIG_DECIMAL_ONE = {{1, 0, 0, 0, 0, 0, 0, 0}};
static const s21_big_decimal BIG_DECIMAL_TEN = {{10, 0, 0, 0, 0, 0, 0, 0}};

void clearDecimalNumber(s21_decimal *number);
void setBitMantissa(s21_decimal *number, int index, int bit);
int getBitMantissa(s21_decimal *number, int index);
int getSign(s21_decimal *number);
void setSign(s21_decimal *number, int sign);
int getIndexHighestBitMantissa(s21_decimal *number);
int getIndexHighestBitUnsigned(unsigned int *number);
int setScale(s21_decimal *number, int exponent);
int getScale(s21_decimal *number);
void leftShift(s21_decimal *number, int shift);

int getBitUnsigned(const unsigned *number, int index);
void copyNumber(s21_decimal *numberDest, s21_decimal *numberSrc);
void copyMantissa(s21_decimal *numberDest, s21_decimal *numberSrc);
int reverseBit(int bit);
void twosComplementNegate(s21_decimal *number);

void handleZeroValues(s21_decimal *number1, s21_decimal *number2);
void handleNegativeNumber(s21_decimal *number);
int handleNegativeNumbers(s21_decimal *number1, s21_decimal *number2);
void handleZeroValue(s21_decimal *number);
void handleSignOverflow(unsigned carry, s21_decimal *number);
int handleReturnValueAdd(s21_decimal *number, int carry, int isEqualSign);
int handleNonZeroRemainder(s21_decimal *divisor, s21_decimal *quotient,
                           s21_decimal *remainder, int *pResultScale);
int handleNegativeScaleForDivision(s21_decimal *result, int *pResultScale);
void handleScaleDown(s21_decimal *number1, s21_decimal *number2);
int handleScaleUp(s21_decimal *number1, s21_decimal *number2);

void normalize(s21_decimal *number1, s21_decimal *number2);
int scaleUp(s21_decimal *number, int scaleDifference);
s21_decimal scaleDown(s21_decimal *number, int scaleDifference);

int compareNumbers(s21_decimal *number1, s21_decimal *number2);
int isEqual(s21_decimal *number1, s21_decimal *number2);
int isLower(s21_decimal *number1, s21_decimal *number2);
int isGreater(s21_decimal *number1, s21_decimal *number2);
int isZero(s21_decimal *number);

int baseAddition(s21_decimal *number1, s21_decimal *number2,
                 s21_decimal *result);
int baseAdditionShell(s21_decimal number1, s21_decimal number2,
                      s21_decimal *result);
int baseMultiply(s21_decimal *number1, s21_decimal *number2,
                 s21_decimal *result);
int baseSubtraction(s21_decimal number1, s21_decimal number2,
                    s21_decimal *result);
int baseDivision(s21_decimal *number1, s21_decimal *number2,
                 s21_decimal *result, s21_decimal *remainder);

int isBigDecimal(s21_big_decimal *number);
int handleScaleOverflowMultiplication(s21_decimal *, s21_decimal *,
                                      s21_decimal *, int);

s21_big_decimal fromDecimalToBigDecimal(s21_decimal *number);
void fromBigDecimalToDecimal(s21_decimal *dest, s21_big_decimal *number);
int normalizeFromBigDecimalToDecimal(s21_decimal *dest, s21_big_decimal *src);

s21_decimal baseMod(s21_decimal *dividend, s21_decimal *divider);
int getCountDigitsInDecimalMantissa(s21_decimal dest);

int handleExtraOneAtTheEndOfDividing(s21_decimal *divider,
                                     s21_decimal *remainder,
                                     s21_decimal *result);

void handleExcessScale(s21_decimal *number);
void handleErrorCodeDivision(s21_decimal *result, int *pErrorCode,
                             int resultScale, int resultSign);

int handleInitialErrorConditionDivision(s21_decimal *number1,
                                        s21_decimal *number2,
                                        s21_decimal *result);

int handleInitialErrorConditionFromFloatToDecimal(float src);

#endif
