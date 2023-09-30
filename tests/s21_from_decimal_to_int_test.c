#include "s21_from_decimal_to_int_test.h"

int main() {
  int errcode = 0;
  case_test(from_decimal_to_int_suite(), &errcode);
  return 0;
}
