#include "s21_negate_test.h"

int main() {
  int errcode = 0;
  case_test(negate_suite(), &errcode);
  return 0;
}
