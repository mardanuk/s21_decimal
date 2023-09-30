#ifndef S21_CONVERSION_H_
#define S21_CONVERSION_H_

#include "s21_common.h"
#include "s21_structs.h"

#define SAVING_NUMBERS_IN_FLOAT 7
#define SIGN_BIT_NUMBER 1
#define EXP_START_BIT_NUMBER 9
#define MANTISSA_START_BIT_NUMBER 24
#define FIRST_BIT_NUMBER_IN_MANTISSA (MANTISSA_START_BIT_NUMBER - 1)
#define FLOAT_EXP_MAX 127

#define S21_NEGATIVE_ONE_FLOAT (-1.f)
#define S21_POSITIVE_ONE_FLOAT (1.f)

int s21_from_int_to_decimal(int src, s21_decimal *dest);

int s21_from_float_to_decimal(float src, s21_decimal *dest);

int s21_from_decimal_to_int(s21_decimal src, int *dest);

int s21_from_decimal_to_float(s21_decimal src, float *dest);

void deleteTrailingZerosInUnsigned(unsigned int *mantissa);

void deleteTrailingZerosInDecimal(s21_decimal *number);

void adjustDecimalForFloatConversion(s21_decimal *dest);

int getScaleFloatNumber(unsigned bits);

unsigned getMantissaFloatNumber(unsigned bits);

unsigned changeBinaryRepresentationFromFloatToUnsigned(float number);

int isZeroInput(float src);

void handleScaleForFloatNumber(int scale, s21_decimal mantissaDecimal,
                               s21_decimal expDecimal, s21_decimal *dest);

float getSingFloat(s21_decimal src);

int handleInitialErrorConditionFromDecimalToFloat(s21_decimal src, float *dest);

#endif