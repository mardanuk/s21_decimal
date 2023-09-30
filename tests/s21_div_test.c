#include "s21_div_test.h"

int main() {
  int errcode = 0;
  case_test(div_suite(), &errcode);
  return 0;
}
