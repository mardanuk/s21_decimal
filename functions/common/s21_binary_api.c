#include "../../headers/s21_common.h"
#include "../../headers/s21_overloads.h"

void setBitMantissa(s21_decimal *number, int index, int bit) {
  if (bit)
    SET_BIT(number->bits[index / S21_SIZEOF_INT_BIT],
            index % S21_SIZEOF_INT_BIT);
  else
    RESET_BIT(number->bits[index / S21_SIZEOF_INT_BIT],
              index % S21_SIZEOF_INT_BIT);
}

int getBitMantissa(s21_decimal *number, int index) {
  return (number->bits[index / S21_SIZEOF_INT_BIT] &
          (1 << index % S21_SIZEOF_INT_BIT)) > 0;
}

int getBitUnsigned(const unsigned *number, int index) {
  return (*number & (1 << index)) > 0;
}

void setSign(s21_decimal *number, int sign) {
  setBitMantissa(number, S21_SIGN_BIT_INDEX, sign);
}

int getSign(s21_decimal *number) {
  return getBitMantissa(number, S21_SIGN_BIT_INDEX);
}

int setScale(s21_decimal *number, int scale) {
  if ((scale < S21_ZERO_SCALE) || scale >= (1 << (index_endExponentBits - 1)))
    return errorCode_scaleIsOutOfBounds;

  int mask = S21_BITMASK_FOR_EXPONENT_BITS;
  int maskToClear = S21_BITMASK_TO_CLEAR_EXPONENT_BITS;
  number->bits[headerBit] &= maskToClear;
  number->bits[headerBit] |= (scale & mask) << index_startExponentBits;
  return errorCode_noError;
}

int getScale(s21_decimal *number) {
  return (int)(number->bits[headerBit] >> index_startExponentBits) &
         S21_BITMASK_FOR_EXPONENT_BITS;
}

void leftShift(s21_decimal *number, int shift) {
  for (int i = S21_MANTISSA_HIGHEST_BIT; i >= shift; i--) {
    unsigned int bit = getBitMantissa(number, i - shift);
    setBitMantissa(number, i, (int)bit);
  }
  for (int i = 0; i < shift; i++) {
    setBitMantissa(number, i, 0);
  }
}

void clearDecimalNumber(s21_decimal *number) {
  for (int i = 0; i < S21_DECIMAL_INT_BITS_COUNT; ++i) number->bits[i] = 0;
}

int isBigDecimal(s21_big_decimal *number) {
  return number->bits[fourthBit_big] || number->bits[fifthBit_big] ||
         number->bits[sixthBit_big] || number->bits[seventhBit_big];
}

s21_big_decimal fromDecimalToBigDecimal(s21_decimal *number) {
  s21_big_decimal result = {{number->bits[firstBit], number->bits[secondBit],
                             number->bits[thirdBit], 0, 0, 0, 0,
                             number->bits[headerBit]}};
  return result;
}

int reverseBit(int bit) { return bit <= 0; }

void fromBigDecimalToDecimal(s21_decimal *dest, s21_big_decimal *number) {
  dest->bits[firstBit] = number->bits[firstBit_big];
  dest->bits[secondBit] = number->bits[secondBit_big];
  dest->bits[thirdBit] = number->bits[thirdBit_big];
  dest->bits[headerBit] = number->bits[headerBit_big];
}

int getIndexHighestBitMantissa(s21_decimal *number) {
  int result = 0;
  for (int i = S21_MANTISSA_SIZE; i > 0 && !result; --i)
    result = getBitMantissa(number, i) ? i : 0;
  return result;
}

int getScale_big(s21_big_decimal *number) {
  unsigned int scaleBits =
      (number->bits[headerBit_big] >> index_startExponentBits) &
      S21_BITMASK_FOR_EXPONENT_BITS;
  return (int)scaleBits;
}

int setScale_big(s21_big_decimal *number, int scale) {
  if ((scale < S21_ZERO_SCALE) || scale >= (1 << (index_endExponentBits - 1))) {
    return errorCode_scaleIsOutOfBounds;
  }
  int mask = S21_BITMASK_FOR_EXPONENT_BITS;
  int maskToClear = S21_BITMASK_TO_CLEAR_EXPONENT_BITS;
  number->bits[headerBit_big] &= maskToClear;
  number->bits[headerBit_big] |= ((scale & mask) << index_startExponentBits);
  return errorCode_noError;
}

int getIndexHighestBitMantissa_big(s21_big_decimal *number) {
  int result = 0;
  for (int i = S21_BIG_MANTISSA_SIZE; i > 0 && !result; --i) {
    result = getBitMantissa_big(number, i) ? i : 0;
  }
  return result;
}

int getSign_big(s21_big_decimal *number) {
  return getBitMantissa_big(number, S21_SIGN_BIT_INDEX_BIG);
}

void setSign_big(s21_big_decimal *number, int sign) {
  setBitMantissa_big(number, S21_SIGN_BIT_INDEX_BIG, sign);
}

int getBitMantissa_big(s21_big_decimal *number, int index) {
  return (number->bits[index / S21_SIZEOF_INT_BIT] &
          (1 << index % S21_SIZEOF_INT_BIT)) > 0;
}

void setBitMantissa_big(s21_big_decimal *number, int index, int bit) {
  if (bit)
    SET_BIT(number->bits[index / S21_SIZEOF_INT_BIT],
            index % S21_SIZEOF_INT_BIT);
  else
    RESET_BIT(number->bits[index / S21_SIZEOF_INT_BIT],
              index % S21_SIZEOF_INT_BIT);
}

void copyNumber_big(s21_big_decimal *numberDest, s21_big_decimal *numberSrc) {
  for (int i = 0; i < S21_BIG_DECIMAL_INT_BITS_COUNT; ++i) {
    numberDest->bits[i] = numberSrc->bits[i];
  }
}

void clearDecimalNumber_big(s21_big_decimal *number) {
  for (int i = 0; i < S21_BIG_DECIMAL_INT_BITS_COUNT; ++i) number->bits[i] = 0;
}

void leftShift_big(s21_big_decimal *number, int shift) {
  for (int i = S21_BIG_MANTISSA_SIZE - 1; i >= shift; i--) {
    unsigned int bit = getBitMantissa_big(number, i - shift);
    setBitMantissa_big(number, i, (int)bit);
  }
  for (int i = 0; i < shift; i++) {
    setBitMantissa_big(number, i, 0);
  }
}
