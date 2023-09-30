#include "s21_develop.h"

void *s21_insert(const char *src, const char *str, int startIndex) {
  char *result = NULL;
  if (src && str && startIndex <= (int)strlen(src)) {
    result = calloc((strlen(src) + strlen(str) + 1), sizeof(char));
    strncpy(result, src, startIndex);
    strncpy(result + startIndex, str, strlen(str));
    strncpy(result + strlen(str) + startIndex, src + startIndex, strlen(src));
  }
  return (void *)result;
}

char *floatToString(float number) {
  char *string = calloc(256, sizeof(char));
  sprintf(string, "%f", number);
  return string;
}

char *decimalToString(s21_decimal *number) {
  char *string = calloc(256, sizeof(char));
  strcat(string, "[");
  for (int i = 3; i >= 0; --i) {
    for (int j = 31; j >= 0; --j) {
      unsigned bit = getBitMantissa(number, i * 32 + j);
      strcat(string, bit ? "1" : "0");
    }
    if (i > 0) strcat(string, "][");
  }
  strcat(string, "]");
  return string;
}

void printNumColorless(const char *text, s21_decimal *number) {
  printf("%s: %s\n", text, decimalToString(number));
  printNumberInDecimalBase(number);
  printf("scale: %d\n\n", getScale(number));
}
/*
 * This function is not handling memory leaks!
 */
void printNum(const char *text, s21_decimal *number) {
  char *string = calloc(1000, sizeof(char));
  strcat(string, "[");
  for (int i = 3; i >= 0; --i) {
    for (int j = 31; j >= 0; --j) {
      unsigned bit = getBitMantissa(number, i * 32 + j);
      strcat(string, bit ? "1" : "0");
    }
    if (i > 0) strcat(string, "][");
  }
  strcat(string, "]");

  string = s21_insert(string, RESET_COLOR, 33 - index_startExponentBits);
  string = s21_insert(string, "\033[32m", 32 - index_endExponentBits);

  string = s21_insert(string, RESET_COLOR, 33 - index_signBit);
  string = s21_insert(string, "\033[31m", 32 - index_signBit);

  printf("%s: sign: %d, scale: %d\n%s\n", text, getSign(number),
         getScale(number), string);
  printNumberInDecimalBase(number);

  free(string);
}

void printNum_big(const char *text, s21_big_decimal *number) {
  char *string = calloc(512, sizeof(char));
  strcat(string, "[");
  for (int i = 7; i >= 0; --i) {
    for (int j = 31; j >= 0; --j) {
      unsigned bit = getBitMantissa_big(number, i * 32 + j);
      strcat(string, bit ? "1" : "0");
    }
    if (i > 0) strcat(string, "][");
  }
  strcat(string, "]");

  string = s21_insert(string, RESET_COLOR, 33 - index_startExponentBits);
  string = s21_insert(string, "\033[32m", 32 - index_endExponentBits);

  string = s21_insert(string, RESET_COLOR, 33 - index_signBit);
  string = s21_insert(string, "\033[31m", 32 - index_signBit);

  printf("%s: sign: %d, scale: %d, bits[0]: %d\n%s\n", text,
         getSign_big(number), getScale_big(number), number->bits[0], string);

  free(string);
}

void writeFile(char *isArithmeticMethod, char *methodNum, char *number1,
               char *number2, char *result) {
  FILE *fPtr = fopen("../test.txt", "w");
  fprintf(fPtr, "%s\n", isArithmeticMethod);
  fprintf(fPtr, "%s\n", methodNum);
  fprintf(fPtr, "0\n%s\n", number1);
  fprintf(fPtr, "0\n%s\n", number2);
  fprintf(fPtr, "0\n%s\n", result);
  fclose(fPtr);
}

void writeFileSingleNumber(char *isArithmeticMethod, char *methodNum,
                           char *number1, char *result) {
  FILE *fPtr = fopen("../test.txt", "w");
  fprintf(fPtr, "%s\n", isArithmeticMethod);
  fprintf(fPtr, "%s\n", methodNum);
  fprintf(fPtr, "0\n%s\n", number1);
  fprintf(fPtr, "0\n%s\n", result);
  fclose(fPtr);
}

void writeFileSingleNumberInDecimal(char *isArithmeticMethod, char *methodNum,
                                    char *number1, char *result) {
  FILE *fPtr = fopen("../test.txt", "w");
  fprintf(fPtr, "%s\n", isArithmeticMethod);
  fprintf(fPtr, "%s\n", methodNum);
  fprintf(fPtr, "%s\n", number1);
  fprintf(fPtr, "0\n%s\n", result);
  fclose(fPtr);
}

void stringReverse(char *string, int length) {
  char tempChar;
  for (int i = 0; i < length / 2; i++) {
    tempChar = string[i];
    string[i] = string[length - i - 1];
    string[length - i - 1] = tempChar;
  }
}
void addingDot(char *dest, char *strWithNumbers, int scale) {
  char *dot = calloc(2, sizeof(char));
  dot[0] = '.';
  int wherePlaceADot = (int)strlen(strWithNumbers) - scale;
  strncat(dest, strWithNumbers, wherePlaceADot);
  if (scale != 0) strncat(dest, dot, 1);
  strcat(dest, strWithNumbers + wherePlaceADot);
  free(dot);
}
char *addScaleAndSignToString(char *str, int len, int scale, int sign) {
  char *tempStr = calloc(130, sizeof(char));
  strcat(tempStr, sign == 1 ? "-" : "");
  for (int i = sign; len <= scale + sign; i++, len++) tempStr[i] = '0';
  strcat(tempStr, str);
  memset(str, 0, len);
  addingDot(str, tempStr, scale);
  free(tempStr);
  return str;
}

char *getNumberStrInDecimalBase(s21_decimal dest, char *stringDecimal) {
  if (!isZero(&dest)) {
    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal remainder = {{0, 0, 0, 0}};
    int stringSize = 0;
    int scale = getScale(&dest);
    int sign = getSign(&dest);
    setSign(&dest, 0);
    for (int i = 0; !isZero(&dest); i++, stringSize = i) {
      baseDivision(&dest, (s21_decimal *)&DECIMAL_TEN, &res, &remainder);
      copyNumber(&dest, &res);
      stringDecimal[i] = remainder.bits[0] + '0';
    }
    stringReverse(stringDecimal, stringSize);
    stringDecimal =
        addScaleAndSignToString(stringDecimal, stringSize + sign, scale, sign);
  } else {
    stringDecimal[0] = '0';
  }
  return stringDecimal;
}

void printNumberInDecimalBase(s21_decimal *dest) {
  char *stringDecimal = calloc(130, sizeof(char));
  printf("In decimal base: %s\n",
         getNumberStrInDecimalBase(*dest, stringDecimal));
  free(stringDecimal);
}