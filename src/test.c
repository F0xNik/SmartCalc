#include <check.h>

#include "C_header.h"

START_TEST(test_plus) {
  char str[256] = "1.25+3.45";
  Calculation(str);
  ck_assert_str_eq("4.700000", str);
}
END_TEST

START_TEST(test_minus) {
  char str[256] = "1.25-3.45";
  Calculation(str);
  ck_assert_str_eq("-2.200000", str);
}
END_TEST

START_TEST(test_mult) {
  char str[256] = "1.25*3.45";
  Calculation(str);
  ck_assert_str_eq("4.312500", str);
}
END_TEST

START_TEST(test_mult2) {
  char str[256] = "3*(4+7)";
  Calculation(str);
  ck_assert_str_eq("33.000000", str);
}
END_TEST

START_TEST(test_div) {
  char str[256] = "1.25/3.45";
  Calculation(str);
  ck_assert_str_eq("0.362319", str);
}
END_TEST

START_TEST(test_mod) {
  char str[256] = "1.25mod3.45";
  Calculation(str);
  ck_assert_str_eq("1.250000", str);
}
END_TEST

START_TEST(test_pow) {
  char str[256] = "1.25^3.45";
  Calculation(str);
  ck_assert_str_eq("2.159432", str);
}
END_TEST

START_TEST(test_brackets) {
  char str[256] = "(5.23+1.25)*(0.25+0.001)";
  Calculation(str);
  ck_assert_str_eq("1.626480", str);
}
END_TEST

START_TEST(test_sin) {
  char str[256] = "sin((5.23+1.25)*(0.25+0.001))";
  Calculation(str);
  ck_assert_str_eq("0.998450", str);
}
END_TEST

START_TEST(test_cos) {
  char str[256] = "cos((5.23+1.25)*(0.25+0.001))";
  Calculation(str);
  ck_assert_str_eq("-0.055655", str);
}
END_TEST

START_TEST(test_tan) {
  char str[256] = "tan((5.23+1.25)*(0.25+0.001))";
  Calculation(str);
  ck_assert_str_eq("-17.940020", str);
}
END_TEST

START_TEST(test_asin) {
  char str[256] = "asin(7/7.7)";
  Calculation(str);
  ck_assert_str_eq("1.141097", str);
}
END_TEST

START_TEST(test_acos) {
  char str[256] = "acos(7/7.7)";
  Calculation(str);
  ck_assert_str_eq("0.429700", str);
}
END_TEST

START_TEST(test_atan) {
  char str[256] = "atan(7/7.7)";
  Calculation(str);
  ck_assert_str_eq("0.737815", str);
}
END_TEST

START_TEST(test_sqrt) {
  char str[256] = "sqrt(1357-245)";
  Calculation(str);
  ck_assert_str_eq("33.346664", str);
}
END_TEST

START_TEST(test_ln) {
  char str[256] = "ln(1357-245)";
  Calculation(str);
  ck_assert_str_eq("7.013915", str);
}
END_TEST

START_TEST(test_log) {
  char str[256] = "log(1357-245)";
  Calculation(str);
  ck_assert_str_eq("3.046105", str);
}
END_TEST

START_TEST(test_combo) {
  char str[256] = "log(32+1)*7/11*432*(sin(2)*12-45+4)/2";
  Calculation(str);
  ck_assert_str_eq("-6280.257182", str);
}
END_TEST

START_TEST(test_combo_func) {
  char str[256] = "cos(sin(tan(-0.005)))";
  Calculation(str);
  ck_assert_str_eq("0.999987", str);
}
END_TEST


int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, test_plus);
  tcase_add_test(tc1_1, test_minus);
  tcase_add_test(tc1_1, test_mult);
  tcase_add_test(tc1_1, test_mult2);
  tcase_add_test(tc1_1, test_div);
  tcase_add_test(tc1_1, test_mod);
  tcase_add_test(tc1_1, test_pow);
  tcase_add_test(tc1_1, test_brackets);
  tcase_add_test(tc1_1, test_sin);
  tcase_add_test(tc1_1, test_cos);
  tcase_add_test(tc1_1, test_tan);
  tcase_add_test(tc1_1, test_asin);
  tcase_add_test(tc1_1, test_acos);
  tcase_add_test(tc1_1, test_atan);
  tcase_add_test(tc1_1, test_sqrt);
  tcase_add_test(tc1_1, test_ln);
  tcase_add_test(tc1_1, test_log);
  tcase_add_test(tc1_1, test_combo);
  tcase_add_test(tc1_1, test_combo_func);

  srunner_run_all(sr, CK_ENV);
  srunner_ntests_failed(sr);
  srunner_free(sr);

  return (0);
}