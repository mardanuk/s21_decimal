#ifndef S21_STRUCTS_H_
#define S21_STRUCTS_H_

union floatUnsignedUnion {
  float floatValue;
  unsigned unsignedValue;
};

typedef struct {
  unsigned bits[4];
} s21_decimal;

typedef enum {
  compareReturnValue_lower = -1,
  compareReturnValue_equal = 0,
  compareReturnValue_greater = 1,
} compareReturnValue;

typedef enum {
  returnValueComparison_false = 0,
  returnValueComparison_true = 1
} returnValueComparison;

typedef enum {
  roundingType_truncate = 0,
  roundingType_round = 1,
  roundingType_floor = 2,
} roundingType;

typedef enum {
  index_startExponentBits = 16,
  index_endExponentBits = 23,
  index_signBit = 31
} indexesOfDecimalNumber;

typedef enum {
  errorCodeArithmetic_noError = 0,
  errorCodeArithmetic_tooLargeOrInfinity = 1,
  errorCodeArithmetic_tooSmallOrNegativeInfinity = 2,
  errorCodeArithmetic_divisionByZero = 3,
} errorCodeArithmetic;

typedef enum {
  errorCodeConversion_noError = 0,
  errorCodeConversion_conversionError = 1,
} errorCodeConversion;

typedef enum {
  errorCode_noError = 0,
  errorCode_numberIsTooSmallOrGreat = -1,
  errorCode_scaleIsOutOfBounds = -2,
} errorCode;

typedef enum {
  firstBit = 0,
  secondBit = 1,
  thirdBit = 2,
  headerBit = 3,
} bitIndicesDecimal;

typedef enum {
  firstBit_big = 0,
  secondBit_big = 1,
  thirdBit_big = 2,
  fourthBit_big = 3,
  fifthBit_big = 4,
  sixthBit_big = 5,
  seventhBit_big = 6,
  headerBit_big = 7,
} bitIndicesBigDecimal;

#endif
