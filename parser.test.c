#include "../shared/str_format_parser.h"
#include "main.h"

START_TEST(parser_correct_init_testing) {
  TStrFormatParse *PFormat = createFormatParse();
  ck_assert_int_eq(PFormat->precision, -1);
  ck_assert_int_eq(PFormat->width, 0);
  ck_assert_int_eq(PFormat->type, 0);
  ck_assert_int_eq(PFormat->formatLength, 0);
  ck_assert_int_eq(PFormat->isIgnore, 0);
  ck_assert_int_eq(PFormat->length, 0);
  ck_assert_int_eq(PFormat->precisionStar, 0);
  ck_assert_int_eq(PFormat->widthStar, 0);
  ck_assert_ptr_nonnull(PFormat->flags);
  ck_assert_int_eq(PFormat->flags->jail, 0);
  ck_assert_int_eq(PFormat->flags->minus, 0);
  ck_assert_int_eq(PFormat->flags->plus, 0);
  ck_assert_int_eq(PFormat->flags->space, 0);
  ck_assert_int_eq(PFormat->flags->zero, 0);
  freeFormatParse(PFormat);
}
END_TEST

START_TEST(parser_correct_testing) {
  char format[] = "%-+ 0#20.15ld";
  TStrFormatParse *PFormat = createFormatParse();
  strFormatParser(format, PFormat);
  ck_assert_int_eq(PFormat->width, 20);
  ck_assert_int_eq(PFormat->precision, 15);
  ck_assert_int_eq(PFormat->length, 'l');
  ck_assert_int_eq(PFormat->type, 'd');
  ck_assert_int_eq(PFormat->flags->jail, 1);
  ck_assert_int_eq(PFormat->flags->minus, 1);
  ck_assert_int_eq(PFormat->flags->plus, 1);
  ck_assert_int_eq(PFormat->flags->space, 1);
  ck_assert_int_eq(PFormat->flags->zero, 1);
  ck_assert_int_eq(PFormat->isIgnore, 0);
  ck_assert_int_eq(PFormat->formatLength, 12);
  freeFormatParse(PFormat);

  char format2[] = "%*.*Lf";
  TStrFormatParse *PFormat2 = createFormatParse();
  strFormatParser(format2, PFormat2);
  ck_assert_int_eq(PFormat2->width, 0);
  ck_assert_int_eq(PFormat2->precision, -1);
  ck_assert_int_eq(PFormat2->widthStar, 1);
  ck_assert_int_eq(PFormat2->precisionStar, 1);
  ck_assert_int_eq(PFormat2->length, 'L');
  ck_assert_int_eq(PFormat2->type, 'f');
  ck_assert_int_eq(PFormat2->isIgnore, 0);
  ck_assert_int_eq(PFormat2->formatLength, 5);
  freeFormatParse(PFormat2);
}
END_TEST

START_TEST(parser_hard_testing) {
  char format[] = "%-+ 0#20.15l";
  TStrFormatParse *PFormat = createFormatParse();
  strFormatParser(format, PFormat);
  ck_assert_int_eq(PFormat->isIgnore, 1);
  freeFormatParse(PFormat);

  char format2[] = "%-+ 0";
  TStrFormatParse *PFormat2 = createFormatParse();
  strFormatParser(format2, PFormat2);
  ck_assert_int_eq(PFormat2->isIgnore, 1);
  freeFormatParse(PFormat2);

  char format3[] = "%-+ 0 ll cringe";
  TStrFormatParse *PFormat3 = createFormatParse();
  strFormatParser(format3, PFormat3);
  ck_assert_int_eq(PFormat3->isIgnore, 1);
  freeFormatParse(PFormat3);
}
END_TEST

Suite *parser_suite() {
  TCase *correct, *correct_init, *hard;
  Suite *s = suite_create("sprintf");

  correct_init = tcase_create("parser correct init work testing");
  tcase_add_test(correct_init, parser_correct_init_testing);
  suite_add_tcase(s, correct_init);

  correct = tcase_create("parser correct work testing");
  tcase_add_test(correct, parser_correct_testing);
  suite_add_tcase(s, correct);

  hard = tcase_create("parser correct work testing");
  tcase_add_test(hard, parser_hard_testing);
  suite_add_tcase(s, hard);

  return s;
}