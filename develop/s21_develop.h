#ifndef S21_DEVELOP_H_
#define S21_DEVELOP_H_

#include <stdio.h>

#include "../headers/s21_common.h"

#define RESET_COLOR "\033[0m"

void *s21_insert(const char *src, const char *str, int startIndex);

void printNum(const char *, s21_decimal *number);

void printNumColorless(const char *text, s21_decimal *number);

char *floatToString(float number);

char *decimalToString(s21_decimal *number);

void writeFile(char *isArithmeticMethod, char *methodNum, char *number1,
               char *number2, char *result);

void writeFileSingleNumber(char *isArithmeticMethod, char *methodNum,
                           char *number1, char *result);

void printNum_big(const char *text, s21_big_decimal *number);

void writeFileSingleNumberInDecimal(char *isArithmeticMethod, char *methodNum,
                                    char *number1, char *result);

void printNumberInDecimalBase(s21_decimal *dest);

char *getNumberStrInDecimalBase(s21_decimal dest, char *stringDecimal);

void addingDot(char *dest, char *strWithNumbers, int scale);

#endif
