#include <stdio.h>

#include "../s21_string.h"
#include "locale.h"
#include "main.h"
#include "string.h"

START_TEST(d_specifier_testing) {
  char result[400];
  char result2[400];
  char result3[400];
  char result4[400];
  char format[] =
      "print: %d %hd %ld, %+d %+d % d %05d %0-5d %-5d %5d %.6d %1d %05d";
  int printCount = sprintf(result, format, __INT_MAX__, __SHRT_MAX__,
                           __LONG_MAX__, 2, 2, 2, 23, 23, 23, 23, 20, 1, 232);
  int printCount2 =
      s21_sprintf(result2, format, __INT_MAX__, __SHRT_MAX__, __LONG_MAX__, 2,
                  2, 2, 23, 23, 23, 23, 20, 1, 232);
  int printCount3 =
      sprintf(result3, format, -__INT_MAX__, -__SHRT_MAX__, -__LONG_MAX__, -2,
              -2, -2, -23, -23, -23, -23, -20, -1, -232);
  int printCount4 =
      s21_sprintf(result4, format, -__INT_MAX__, -__SHRT_MAX__, -__LONG_MAX__,
                  -2, -2, -2, -23, -23, -23, -23, -20, -1, -232);
  ck_assert_str_eq(result, result2);
  ck_assert_str_eq(result3, result4);
  ck_assert_int_eq(printCount, printCount2);
  ck_assert_int_eq(printCount3, printCount4);
}
END_TEST

START_TEST(u_specifier_testing) {
  char result[400];
  char result2[400];
  char format[] =
      "print: %u %hu %lu, %+u %+u % u %05u %0-5u %-5u %5u %.6u %05u";
  int printCount = sprintf(result, format, __INT16_MAX__, __INT32_MAX__,
                           __INT64_MAX__, 2, 2, 2, 23, 23, 23, 23, 20, 232);
  int printCount2 =
      s21_sprintf(result2, format, __INT16_MAX__, __INT32_MAX__, __INT64_MAX__,
                  2, 2, 2, 23, 23, 23, 23, 20, 232);
  ck_assert_str_eq(result, result2);
  ck_assert_int_eq(printCount, printCount2);
}
END_TEST

START_TEST(x_specifier_testing) {
  char result[400];
  char result2[400];
  char format[] =
      "print: %x %hx %lx, %+x %+x % x %05x %0-5x %-5x %5x %.6x %#x %05x";
  int printCount =
      sprintf(result, format, __INT16_MAX__, __INT32_MAX__, __INT64_MAX__, 2, 2,
              2, 23, 23, 23, 23, 20, 222, 232);
  int printCount2 =
      s21_sprintf(result2, format, __INT16_MAX__, __INT32_MAX__, __INT64_MAX__,
                  2, 2, 2, 23, 23, 23, 23, 20, 222, 232);
  ck_assert_str_eq(result, result2);
  ck_assert_int_eq(printCount, printCount2);
}
END_TEST

START_TEST(X_specifier_testing) {
  char result[400];
  char result2[400];
  char format[] =
      "print: %X %hX %lX, %+X %+X % X %05X %0-5X %-5X %5X %.6X %#X %05X";
  int printCount =
      sprintf(result, format, __INT16_MAX__, __INT32_MAX__, __INT64_MAX__, 2, 2,
              2, 23, 23, 23, 23, 20, 2222, 232);
  int printCount2 =
      s21_sprintf(result2, format, __INT16_MAX__, __INT32_MAX__, __INT64_MAX__,
                  2, 2, 2, 23, 23, 23, 23, 20, 2222, 232);
  ck_assert_str_eq(result, result2);
  ck_assert_int_eq(printCount, printCount2);
}
END_TEST

START_TEST(o_specifier_testing) {
  char result[400];
  char result2[400];
  char format[] =
      "print: %o %ho %lo, %+o %+o % o %05o %0-5o %-5o %5o %.6o %#o %05o";
  int printCount =
      sprintf(result, format, __INT16_MAX__, __INT32_MAX__, __INT64_MAX__, 2, 2,
              2, 23, 23, 23, 23, 20, 222, 232);
  int printCount2 =
      s21_sprintf(result2, format, __INT16_MAX__, __INT32_MAX__, __INT64_MAX__,
                  2, 2, 2, 23, 23, 23, 23, 20, 222, 232);
  ck_assert_str_eq(result, result2);
  ck_assert_int_eq(printCount, printCount2);
}
END_TEST

START_TEST(percent_specifier_testing) {
  char result[400];
  char result2[400];
  char format[] = "print: %% %#% %-020.10% %.10l% %10h% % #L% %d %05%";
  int printCount = sprintf(result, format, 232);
  int printCount2 = s21_sprintf(result2, format, 232);
  ck_assert_str_eq(result, result2);
  ck_assert_int_eq(printCount, printCount2);
}
END_TEST

START_TEST(c_specifier_testing) {
  setlocale(LC_ALL, "");
  char result[400];
  char result2[400];
  char format[] =
      "print: %c %5c %.20c %+c %-5c %#c % c %05c %lc %5lc %.20lc %+lc %-5lc "
      "%#lc % lc %0lc lol";
  int printCount =
      sprintf(result, format, 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', L'ん',
              L'ん', L'ん', L'ん', L'ん', L'ん', L'ん', L'ん');
  int printCount2 =
      s21_sprintf(result2, format, 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a',
                  L'ん', L'ん', L'ん', L'ん', L'ん', L'ん', L'ん', L'ん');
  ck_assert_str_eq(result, result2);
  ck_assert_int_eq(printCount, printCount2);
}
END_TEST

START_TEST(s_specifier_testing) {
  setlocale(LC_ALL, "");
  char result[400];
  char result2[400];
  char format[] =
      "print: %s % s %#s %-s %+s %5s %-5s %.3s %05s %ls % ls %#ls %-ls %+ls "
      "%5ls %-5ls %.3ls %s %.3s %ls %.3ls %05ls lol";
  int printCount =
      sprintf(result, format, "league", "league", "league", "league", "league",
              "league", "league", "league", "league", L"😁こんにちは日本",
              L"😁こんにちは日本", L"😁こんにちは日本", L"😁こんにちは日本",
              L"😁こんにちは日本", L"😁こんにちは日本", L"😁こんにちは日本",
              L"😁こんにちは日本", NULL, NULL, NULL, NULL, L"😁こんにちは日本");
  int printCount2 = s21_sprintf(
      result2, format, "league", "league", "league", "league", "league",
      "league", "league", "league", "league", L"😁こんにちは日本",
      L"😁こんにちは日本", L"😁こんにちは日本", L"😁こんにちは日本",
      L"😁こんにちは日本", L"😁こんにちは日本", L"😁こんにちは日本",
      L"😁こんにちは日本", NULL, NULL, NULL, NULL, L"😁こんにちは日本");
  ck_assert_str_eq(result, result2);
  ck_assert_int_eq(printCount, printCount2);
}
END_TEST

START_TEST(f_specifier_testing) {
  char result[400];
  char result2[400];
  char format[] =
      "print: %.*f %5f %-5f %0f % f %+f %#f %.1f %.10f %.23f %#.0f %lf %f lol";
  int printCount =
      sprintf(result, format, 4, 50.91, 50.214, 50.87, 50.878787, 50.87687,
              50.7777, 50.4655, 50.87769, 50.65554, 50.6558, 50.866427659,
              100000000000.76443553, 50.75475465);
  int printCount2 =
      s21_sprintf(result2, format, 4, 50.91, 50.214, 50.87, 50.878787, 50.87687,
                  50.7777, 50.4655, 50.87769, 50.65554, 50.6558, 50.866427659,
                  100000000000.76443553, 50.75475465);
  char result3[400];
  char result4[400];
  int printCount3 =
      sprintf(result3, format, 4, -50.91, -50.214, -50.87, -50.878787,
              -50.87687, -50.7777, -50.4655, -50.87769, -50.65554, -50.6558,
              -50.866427659, -100000000000.76443553, -50.75475465);
  int printCount4 =
      s21_sprintf(result4, format, 4, -50.91, -50.214, -50.87, -50.878787,
                  -50.87687, -50.7777, -50.4655, -50.87769, -50.65554, -50.6558,
                  -50.866427659, -100000000000.76443553, -50.75475465);
  ck_assert_str_eq(result, result2);
  ck_assert_str_eq(result3, result4);
  ck_assert_int_eq(printCount, printCount2);
  ck_assert_int_eq(printCount3, printCount4);
}
END_TEST

START_TEST(p_specifier_testing) {
  char result[400];
  char result2[400];
  char format[] = "print: %p %#p %05p %-5p %+p % p %5p %.20p";
  int printCount = sprintf(result, format, result, result, result, result,
                           result, result, result, result);
  int printCount2 = s21_sprintf(result2, format, result, result, result, result,
                                result, result, result, result);
  ck_assert_str_eq(result, result2);
  ck_assert_int_eq(printCount, printCount2);
}
END_TEST

START_TEST(e_specifier_testing) {
  char result[400];
  char result2[400];
  char format[] =
      "print: %.*e %5e %-5e %0e % e %+e %#e %.1e %.10e %.15e %#e %le %e lol";
  int printCount =
      sprintf(result, format, 4, 50.91, 50.214, 50.87, 50.878787, 50.87687,
              50.7777, 50.4655, 50.87769, 50.65554, 50.6558, 50.866427659,
              100000000000.76443553, 50.75475465);
  int printCount2 =
      s21_sprintf(result2, format, 4, 50.91, 50.214, 50.87, 50.878787, 50.87687,
                  50.7777, 50.4655, 50.87769, 50.65554, 50.6558, 50.866427659,
                  100000000000.76443553, 50.75475465);
  ck_assert_str_eq(result, result2);
  ck_assert_int_eq(printCount, printCount2);
}
END_TEST

START_TEST(E_specifier_testing) {
  char result[400];
  char result2[400];
  char format[] =
      "print: %.*E %5E %-5E %0E % E %+E %#E %.1E %.10E %.15E %#E %lE %E lol";
  int printCount =
      sprintf(result, format, 4, 50.91, 50.214, 50.87, 50.878787, 50.87687,
              50.7777, 50.4655, 50.87769, 50.65554, 50.6558, 50.866427659,
              13214413214.76443553, 50.75475465);
  int printCount2 =
      s21_sprintf(result2, format, 4, 50.91, 50.214, 50.87, 50.878787, 50.87687,
                  50.7777, 50.4655, 50.87769, 50.65554, 50.6558, 50.866427659,
                  13214413214.76443553, 50.75475465);
  ck_assert_str_eq(result, result2);
  ck_assert_int_eq(printCount, printCount2);
}
END_TEST

START_TEST(g_specifier_testing) {
  char result[400];
  char result2[400];
  char format[] =
      "print: %.*g %5g %-5g %0g % g %+g %#g %.1g %.10g %.9g %#g %lg %g lol";
  int printCount =
      sprintf(result, format, 4, 50.91, 50.214, 50.87, 50.878787, 50.87687,
              50.7777, 50.4655, 50.87769, 50.65554, 50.6558, 50.866427659,
              13214413214.76443553, 50.75475465);
  int printCount2 =
      s21_sprintf(result2, format, 4, 50.91, 50.214, 50.87, 50.878787, 50.87687,
                  50.7777, 50.4655, 50.87769, 50.65554, 50.6558, 50.866427659,
                  13214413214.76443553, 50.75475465);
  ck_assert_str_eq(result, result2);
  ck_assert_int_eq(printCount, printCount2);
}
END_TEST

START_TEST(G_specifier_testing) {
  char result[400];
  char result2[400];
  char format[] =
      "print: %.*G %5G %-5G %0G % G %+G %#G %.1G %.10G %.9G %#G %lG %G lol";
  int printCount =
      sprintf(result, format, 4, 50.91, 50.214, 50.87, 50.878787, 50.87687,
              50.7777, 50.4655, 50.87769, 50.65554, 50.6558, 50.866427659,
              13214413214.76443553, 50.75475465);
  int printCount2 =
      s21_sprintf(result2, format, 4, 50.91, 50.214, 50.87, 50.878787, 50.87687,
                  50.7777, 50.4655, 50.87769, 50.65554, 50.6558, 50.866427659,
                  13214413214.76443553, 50.75475465);
  ck_assert_str_eq(result, result2);
  ck_assert_int_eq(printCount, printCount2);
}
END_TEST

Suite *sprintf_suite() {
  TCase *d_specifier, *u_specifier, *x_specifier, *X_specifier, *o_specifier,
      *percent_specifier, *c_specifier, *s_specifier, *f_specifier,
      *p_specifier, *e_specifier, *E_specifier, *g_specifier, *G_specifier;
  Suite *s = suite_create("sprintf");

  d_specifier = tcase_create("d specifier testing");
  tcase_add_test(d_specifier, d_specifier_testing);
  suite_add_tcase(s, d_specifier);

  u_specifier = tcase_create("u specifier testing");
  tcase_add_test(u_specifier, u_specifier_testing);
  suite_add_tcase(s, u_specifier);

  X_specifier = tcase_create("X specifier testing");
  tcase_add_test(X_specifier, X_specifier_testing);
  suite_add_tcase(s, X_specifier);

  x_specifier = tcase_create("x specifier testing");
  tcase_add_test(x_specifier, x_specifier_testing);
  suite_add_tcase(s, x_specifier);

  o_specifier = tcase_create("o specifier testing");
  tcase_add_test(o_specifier, o_specifier_testing);
  suite_add_tcase(s, o_specifier);

  percent_specifier = tcase_create("percent specifier testing");
  tcase_add_test(percent_specifier, percent_specifier_testing);
  suite_add_tcase(s, percent_specifier);

  c_specifier = tcase_create("c specifier testing");
  tcase_add_test(c_specifier, c_specifier_testing);
  suite_add_tcase(s, c_specifier);

  s_specifier = tcase_create("c specifier testing");
  tcase_add_test(s_specifier, s_specifier_testing);
  suite_add_tcase(s, s_specifier);

  f_specifier = tcase_create("f specifier testing");
  tcase_add_test(f_specifier, f_specifier_testing);
  suite_add_tcase(s, f_specifier);

  p_specifier = tcase_create("p specifier testing");
  tcase_add_test(p_specifier, p_specifier_testing);
  suite_add_tcase(s, p_specifier);

  e_specifier = tcase_create("e specifier testing");
  tcase_add_test(e_specifier, e_specifier_testing);
  suite_add_tcase(s, e_specifier);

  E_specifier = tcase_create("E specifier testing");
  tcase_add_test(E_specifier, E_specifier_testing);
  suite_add_tcase(s, E_specifier);

  g_specifier = tcase_create("g specifier testing");
  tcase_add_test(g_specifier, g_specifier_testing);
  suite_add_tcase(s, g_specifier);

  G_specifier = tcase_create("G specifier testing");
  tcase_add_test(G_specifier, G_specifier_testing);
  suite_add_tcase(s, G_specifier);

  return s;
}