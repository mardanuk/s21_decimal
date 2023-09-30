#include "s21_mul_test.h"

int main() {
  int errcode = 0;
  case_test(mul_suite(), &errcode);
  return 0;
}
