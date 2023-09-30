#include "s21_from_float_to_decimal_test.h"

int main() {
  int errcode = 0;
  case_test(from_float_to_decimal_suite(), &errcode);
  return 0;
}
