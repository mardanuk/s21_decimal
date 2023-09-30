#include "../../headers/s21_conversion.h"
#include "../../headers/s21_rounding.h"

int s21_from_decimal_to_int(s21_decimal src, int *dest) {
  int error = s21_truncate(src, &src);
  int sign = getSign(&src);
  *dest = 0;
  if (!error) {
    int isNumberOutTheBounds;
    isNumberOutTheBounds = (
#ifdef __linux__
        (sign == 0 && src.bits[firstBit] > (unsigned)INT_MAX) ||
        (sign == 1 && src.bits[firstBit] > (unsigned)INT_MIN)
#else
        (sign == 0 && src.bits[firstBit] > (unsigned)INT32_MAX) ||
        (sign == 1 && src.bits[firstBit] > (unsigned)INT32_MIN)
#endif
    );
    if (src.bits[secondBit] != 0 || src.bits[thirdBit] != 0 ||
        isNumberOutTheBounds) {
      error = errorCodeConversion_conversionError;
    } else {
      *dest = (int)src.bits[firstBit];
      *dest = sign == 0 ? *dest : -(*dest);
    }
  }
  return error;
}
