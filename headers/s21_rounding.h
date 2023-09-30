#ifndef S21_ROUNDING_H_
#define S21_ROUNDING_H_

#include "s21_common.h"
#include "s21_structs.h"

int s21_floor(s21_decimal number, s21_decimal *result);

int s21_round(s21_decimal number, s21_decimal *result);

int s21_truncate(s21_decimal number, s21_decimal *result);

int rounding(s21_decimal number, s21_decimal *result, roundingType type);

#endif