#include "s21_add_test.h"

int main() {
  int errcode = 0;
  case_test(add_suite(), &errcode);
  return 0;
}
