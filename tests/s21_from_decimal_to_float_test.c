#include "s21_from_decimal_to_float_test.h"

int main() {
  int errcode = 0;
  case_test(from_decimal_to_float_suite(), &errcode);
  return 0;
}
