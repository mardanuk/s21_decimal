#include "../../headers/s21_rounding.h"

int s21_round(s21_decimal number, s21_decimal *result) {
  return rounding(number, result, roundingType_round);
}
