#include "main_test.h"

int main() {
  int errcode = 0;
  case_test(add_suite(), &errcode);
  case_test(sub_suite(), &errcode);
  case_test(mul_suite(), &errcode);
  case_test(div_suite(), &errcode);
  case_test(negate_suite(), &errcode);
  case_test(floor_suite(), &errcode);
  case_test(is_equal_suite(), &errcode);
  case_test(is_greater_suite(), &errcode);
  case_test(is_greater_or_equal_suite(), &errcode);
  case_test(is_less_suite(), &errcode);
  case_test(is_less_or_equal_suite(), &errcode);
  case_test(is_equal_suite(), &errcode);
  case_test(is_not_equal_suite(), &errcode);
  case_test(round_suite(), &errcode);
  case_test(truncate_suite(), &errcode);
  case_test(from_decimal_to_int_suite(), &errcode);
  case_test(from_int_to_decimal_suite(), &errcode);
  case_test(from_float_to_decimal_suite(), &errcode);
  case_test(from_decimal_to_float_suite(), &errcode);
  return errcode;
}
