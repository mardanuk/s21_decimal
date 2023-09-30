#include "s21_round_test.h"

int main() {
  int errcode = 0;
  case_test(round_suite(), &errcode);
  return 0;
}
