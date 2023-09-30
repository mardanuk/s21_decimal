#include "s21_truncate_test.h"

int main() {
  int errcode = 0;
  case_test(truncate_suite(), &errcode);
  return 0;
}
