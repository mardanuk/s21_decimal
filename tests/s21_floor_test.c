#include "s21_floor_test.h"

int main() {
  int errcode = 0;
  case_test(floor_suite(), &errcode);
  return 0;
}
