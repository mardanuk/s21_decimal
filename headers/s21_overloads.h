#include "s21_structs.h"

#ifndef S21_OVERLOADS_H_
#define S21_OVERLOADS_H_

#define S21_BIG_MANTISSA_SIZE ((int)(S21_SIZEOF_INT_BIT * 7))

typedef struct {
  unsigned bits[8];
} s21_big_decimal;

void setBitMantissa_big(s21_big_decimal *number, int index, int bit);

int getBitMantissa_big(s21_big_decimal *number, int index);

void setSign_big(s21_big_decimal *number, int sign);

int getSign_big(s21_big_decimal *number);

int getIndexHighestBitMantissa_big(s21_big_decimal *number);

int setScale_big(s21_big_decimal *number, int exponent);

int getScale_big(s21_big_decimal *number);

int compareNumbers_big(const s21_big_decimal *number1,
                       const s21_big_decimal *number2);

int isGreater_big(const s21_big_decimal *number1,
                  const s21_big_decimal *number2);

int isZero_big(s21_big_decimal *number);

void copyNumber_big(s21_big_decimal *numberDest, s21_big_decimal *numberSrc);

void twosComplementNegate_big(s21_big_decimal *number);
void twosComplementNegate_big(s21_big_decimal *number);

void leftShift_big(s21_big_decimal *number, int shift);

void clearDecimalNumber_big(s21_big_decimal *number);

void handleZeroValues_big(s21_big_decimal *number1, s21_big_decimal *number2);

void handleZeroValue_big(s21_big_decimal *number);

void handleSignOverflow_big(unsigned carry, s21_big_decimal *number);

void handleNegativeNumber_big(s21_big_decimal *number);

int handleNegativeNumbers_big(s21_big_decimal *number1,
                              s21_big_decimal *number2);

int handleReturnValueAdd_big(s21_big_decimal *number, unsigned carry,
                             int isEqualSign);

int handleReturnValueMul_big(s21_big_decimal *number1,
                             s21_big_decimal *number2);

int scaleUp_big(s21_big_decimal *number, int scaleDifference);

void scaleDown_big(s21_big_decimal *number, int scaleDifference);

int handleScaleUp_big(s21_big_decimal *number1, s21_big_decimal *number2);

void handleScaleDown_big(s21_big_decimal *number1, s21_big_decimal *number2);

void normalize_big(s21_big_decimal *number1, s21_big_decimal *number2);

unsigned baseAddition_big(s21_big_decimal *number1, s21_big_decimal *number2,
                          s21_big_decimal *result);

int baseSubtraction_big(s21_big_decimal number1, s21_big_decimal number2,
                        s21_big_decimal *result);

int baseDivision_big(s21_big_decimal *number1, s21_big_decimal *number2,
                     s21_big_decimal *result, s21_big_decimal *remainder);

int baseMultiplication_big(s21_big_decimal *number1, s21_big_decimal *number2,
                           s21_big_decimal *result);

int baseMultiply_big(s21_big_decimal *number1, s21_big_decimal *number2,
                     s21_big_decimal *result);

#endif
