#include "string.h"

#include <stdio.h>

#include "../s21_string.h"
#include "main.h"

START_TEST(strlen_testing) {
  char value[] = "text text";
  ck_assert_uint_eq(strlen(value), s21_strlen(value));
}
END_TEST

START_TEST(strchr_testing) {
  char value[] = "league of legend wild rift";
  ck_assert_int_eq(*strchr(value, 'w'), *s21_strchr(value, 'w'));
  ck_assert_ptr_eq(strchr(value, 'k'), s21_strchr(value, 'k'));
  ck_assert_ptr_null(s21_strchr(value, 'k'));
}
END_TEST

START_TEST(strrchr_testing) {
  char value[] = "league of legend wild rift";
  ck_assert_int_eq(*strrchr(value, 'e'), *s21_strrchr(value, 'e'));
  ck_assert_ptr_eq(strrchr(value, 'k'), s21_strrchr(value, 'k'));
  ck_assert_ptr_null(s21_strrchr(value, 'k'));
}
END_TEST

START_TEST(strncmp_testing) {
  char value[] = "league of legend wild rift";
  char value2[] = "league of legend wild rift";
  char value3[] = "league of legend";
  char value4[] = "league legend";
  int n = 27;
  ck_assert_int_eq(strncmp(value, value2, n), s21_strncmp(value, value2, n));
  ck_assert_int_eq(strncmp(value, value2, 6), s21_strncmp(value, value2, 6));
  ck_assert_int_eq(strncmp(value, value3, 6), s21_strncmp(value, value3, 6));
  ck_assert_int_eq(strncmp(value, value3, n - 10),
                   s21_strncmp(value, value3, n - 10));
  ck_assert_int_eq(strncmp(value3, value, n), s21_strncmp(value3, value, n));
  ck_assert_int_eq(strncmp(value3, value4, n - 10),
                   s21_strncmp(value3, value4, n - 10));
  ck_assert_int_eq(strncmp(value4, value3, n - 10),
                   s21_strncmp(value4, value3, n - 10));
}
END_TEST

START_TEST(strncat_testing) {
  char value[36] = "league of legend wild rift";
  char value2[36] = "league of legend wild rift";
  char valueSrc[] = "all stars";
  int valueN = 9;
  ck_assert_str_eq(strncat(value, valueSrc, valueN),
                   s21_strncat(value2, valueSrc, valueN));
  char value3[100] = "lolxdlolxd";
  char value4[100] = "lolxdlolxd";
  ck_assert_str_eq(strncat(value3, valueSrc, valueN),
                   s21_strncat(value4, valueSrc, valueN));
  ck_assert_str_eq(strncat(value3, valueSrc, valueN + 3),
                   s21_strncat(value4, valueSrc, valueN + 3));
  ck_assert_str_eq(strncat(value3, valueSrc, valueN - 3),
                   s21_strncat(value4, valueSrc, valueN - 3));
}
END_TEST

START_TEST(strncpy_testing) {
  char value[100] = "";
  char value2[100] = "";
  char valueSrc[] = "all stars";
  int valueN = 9;
  ck_assert_str_eq(strncpy(value, valueSrc, valueN),
                   s21_strncpy(value2, valueSrc, valueN));
  char value3[100] = "lolxdlolxd ";
  char value4[100] = "lolxdlolxd ";
  ck_assert_str_eq(strncpy(value3, valueSrc, valueN),
                   s21_strncpy(value4, valueSrc, valueN));
  ck_assert_str_eq(strncpy(value3, valueSrc, valueN + 3),
                   s21_strncpy(value4, valueSrc, valueN + 3));
  ck_assert_str_eq(strncpy(value3, valueSrc, valueN - 3),
                   s21_strncpy(value4, valueSrc, valueN - 3));
  char value5[36] = "league of legend wild rift";
  char value6[36] = "league of legend wild rift";
  ck_assert_str_eq(strncpy(value5, valueSrc, valueN),
                   s21_strncpy(value6, valueSrc, valueN));
}
END_TEST

START_TEST(strcspn_testing) {
  char value[] = "league of legend wild rift";
  char exceptions[] = "eu";
  ck_assert_uint_eq(strcspn(value, exceptions), s21_strcspn(value, exceptions));
  ck_assert_uint_eq(strcspn(value, "v"), s21_strcspn(value, "v"));
  ck_assert_uint_eq(strcspn(value, " "), s21_strcspn(value, " "));
}
END_TEST

START_TEST(strstr_testing) {
  char value[] = "league of legend wild rift";
  char search[] = "of";
  ck_assert_str_eq(strstr(value, search), s21_strstr(value, search));
  ck_assert_ptr_null(strstr(value, "not"));
  ck_assert_ptr_null(s21_strstr(value, "not"));
  ck_assert_str_eq(strstr(value, "t"), s21_strstr(value, "t"));
  ck_assert_str_eq(strstr(value, "e"), s21_strstr(value, "e"));
  ck_assert_str_eq(strstr(value, " "), s21_strstr(value, " "));
  ck_assert_str_eq(strstr(value, " of"), s21_strstr(value, " of"));
}
END_TEST

START_TEST(strpbrk_testing) {
  char value[] = "league of legend wild rift";
  char findSym1[] = "zv";
  char findSym2[] = "wt";
  ck_assert_str_eq(strpbrk(value, findSym2), s21_strpbrk(value, findSym2));
  ck_assert_ptr_null(s21_strpbrk(value, findSym1));
}
END_TEST

START_TEST(memchr_testing) {
  char value[] = "League of Legends wild rift";
  ck_assert_ptr_eq(memchr(value, 'o', sizeof(value)),
                   s21_memchr(value, 'o', sizeof(value)));
  ck_assert_ptr_eq(memchr(value, 'i', sizeof(value)),
                   s21_memchr(value, 'i', sizeof(value)));
  ck_assert_ptr_null(s21_memchr(value, 't', 1));
  ck_assert_ptr_null(s21_memchr(value, 'Z', sizeof(value)));
}
END_TEST

START_TEST(memcmp_testing) {
  char value[] = "league of legend wild rift";
  char value2[] = "league of legend wild rift";
  char value3[] = "league of legend";
  char value4[] = "league legend";
  ck_assert_int_eq(memcmp(value, value2, sizeof(value)),
                   s21_memcmp(value, value2, sizeof(value)));
  ck_assert_int_eq(memcmp(value, value3, sizeof(value3)),
                   s21_memcmp(value, value3, sizeof(value3)));
  ck_assert_int_eq(memcmp(value, value2, 8), s21_memcmp(value, value2, 8));
  ck_assert_int_eq(memcmp(value, value3, 8), s21_memcmp(value, value3, 8));
  ck_assert_int_eq(memcmp(value, value4, 4), s21_memcmp(value, value4, 4));
  ck_assert_int_eq(memcmp(value, value4, sizeof(value4)),
                   s21_memcmp(value, value4, sizeof(value4)));
}
END_TEST

START_TEST(memcpy_testing) {
  char value[100] = "";
  char value2[100] = "";
  char valueSrc[] = "all stars";

  memcpy(value, valueSrc, sizeof(valueSrc));
  s21_memcpy(value2, valueSrc, sizeof(valueSrc));
  ck_assert_str_eq(value, value2);

  char value3[100] = "lolxdlolxd ";
  char value4[100] = "lolxdlolxd ";

  memcpy(value3, valueSrc, sizeof(valueSrc));
  s21_memcpy(value4, valueSrc, sizeof(valueSrc));
  ck_assert_str_eq(value3, value4);

  memcpy(value3, valueSrc, sizeof(valueSrc));
  s21_memcpy(value4, valueSrc, sizeof(valueSrc));
  ck_assert_str_eq(value3, value4);

  memcpy(value3, valueSrc, sizeof(valueSrc) - 2);
  s21_memcpy(value4, valueSrc, sizeof(valueSrc) - 2);
  ck_assert_str_eq(value3, value4);

  char value5[36] = "league of legend wild rift";
  char value6[36] = "league of legend wild rift";

  memcpy(value5, valueSrc, sizeof(valueSrc));
  s21_memcpy(value6, valueSrc, sizeof(valueSrc));
  ck_assert_str_eq(value5, value6);
}
END_TEST

START_TEST(memset_testing) {
  char value[100] = "";
  char value2[100] = "";

  memset(value, 'c', 10);
  s21_memset(value2, 'c', 10);
  ck_assert_str_eq(value, value2);

  char value3[100] = "lolxdlolxd";
  char value4[100] = "lolxdlolxd";

  memset(value3, 'c', 10);
  s21_memset(value4, 'c', 10);
  ck_assert_str_eq(value3, value4);
}
END_TEST

START_TEST(strerror_testing) {
  for (int i = 0; i < 134; i++) {
    ck_assert_str_eq(strerror(i), s21_strerror(i));
  }
}
END_TEST

void strtok_test(char s21_haystack[], char str_haystack[], char delim[]) {
  char *my_res = s21_strtok(s21_haystack, delim);
  char *std_res = strtok(str_haystack, delim);

  while (my_res && std_res) {
    ck_assert_str_eq(my_res, std_res);
    my_res = s21_strtok(NULL, delim);
    std_res = strtok(NULL, delim);
  }

  ck_assert_str_eq(s21_haystack, str_haystack);
  ck_assert_ptr_eq(my_res, std_res);
}

START_TEST(strtok_testing) {
  char *s21_value2 = "Hello, world!";
  char *str_value2 = "Hello, world!";
  strtok_test(s21_value2, str_value2, ".");
  char *s21_value3 = "._.";
  char *str_value3 = "._.";
  strtok_test(s21_value3, str_value3, "._");
}
END_TEST

START_TEST(to_upper_testing) {
  const char value1[] = "TEst";
  char result1[] = "TEST";
  const char value2[] = "TEst test";
  char result2[] = "TEST TEST";
  const char value3[] = "TEst656test";
  char result3[] = "TEST656TEST";
  ck_assert_str_eq(result1, s21_to_upper(value1));
  ck_assert_str_eq(result2, s21_to_upper(value2));
  ck_assert_str_eq(result3, s21_to_upper(value3));
}
END_TEST

START_TEST(to_lower_testing) {
  const char value1[] = "TEst";
  char result1[] = "test";
  const char value2[] = "TEst test";
  char result2[] = "test test";
  const char value3[] = "TEst656test";
  char result3[] = "test656test";
  ck_assert_str_eq(result1, s21_to_lower(value1));
  ck_assert_str_eq(result2, s21_to_lower(value2));
  ck_assert_str_eq(result3, s21_to_lower(value3));
}
END_TEST

START_TEST(insert_testing) {
  const char src[] = "tut";
  const char value1[] = "TesT";
  char result1[] = "tuTesTt";
  char result2[] = "tTesTut";
  char result3[] = "TesTtut";
  ck_assert_str_eq(result1, s21_insert(src, value1, 2));
  ck_assert_str_eq(result2, s21_insert(src, value1, 1));
  ck_assert_str_eq(result3, s21_insert(src, value1, 0));
}
END_TEST

START_TEST(trim_testing) {
  const char src1[] = "t3xu//r3t3";
  const char trim_chars1[] = "3/rx";
  const char src2[] = "thgut";
  const char trim_chars2[] = "hg";
  const char src3[] = "tutjopa";
  const char trim_chars3[] = "jopa";
  char result[] = "tut";
  ck_assert_str_eq(result, s21_trim(src1, trim_chars1));
  ck_assert_str_eq(result, s21_trim(src2, trim_chars2));
  ck_assert_str_eq(result, s21_trim(src3, trim_chars3));
}
END_TEST

Suite *string_suite() {
  TCase *strlen, *strchr, *strrchr, *strncmp, *strncat, *strncpy, *strcspn,
      *strstr, *strpbrk, *memchr, *memcmp, *memcpy, *memset, *strerror, *strtok,
      *to_upper, *to_lower, *insert, *trim;
  Suite *s = suite_create("String");

  strlen = tcase_create("strlen");
  tcase_add_test(strlen, strlen_testing);
  suite_add_tcase(s, strlen);

  strchr = tcase_create("strchr");
  tcase_add_test(strchr, strchr_testing);
  suite_add_tcase(s, strchr);

  strrchr = tcase_create("strrchr");
  tcase_add_test(strrchr, strrchr_testing);
  suite_add_tcase(s, strrchr);

  strncmp = tcase_create("strncmp");
  tcase_add_test(strncmp, strncmp_testing);
  suite_add_tcase(s, strncmp);

  strncat = tcase_create("strncat");
  tcase_add_test(strncat, strncat_testing);
  suite_add_tcase(s, strncat);

  strncpy = tcase_create("strncpy");
  tcase_add_test(strncpy, strncpy_testing);
  suite_add_tcase(s, strncpy);

  strcspn = tcase_create("strcspn");
  tcase_add_test(strcspn, strcspn_testing);
  suite_add_tcase(s, strcspn);

  strstr = tcase_create("strstr");
  tcase_add_test(strstr, strstr_testing);
  suite_add_tcase(s, strstr);

  strpbrk = tcase_create("strpbrk");
  tcase_add_test(strpbrk, strpbrk_testing);
  suite_add_tcase(s, strpbrk);

  memchr = tcase_create("memchr");
  tcase_add_test(memchr, memchr_testing);
  suite_add_tcase(s, memchr);

  memcmp = tcase_create("memcmp");
  tcase_add_test(memcmp, memcmp_testing);
  suite_add_tcase(s, memcmp);

  memcpy = tcase_create("memcpy");
  tcase_add_test(memcpy, memcpy_testing);
  suite_add_tcase(s, memcpy);

  memset = tcase_create("memset");
  tcase_add_test(memset, memset_testing);
  suite_add_tcase(s, memset);

  strerror = tcase_create("strerror");
  tcase_add_test(strerror, strerror_testing);
  suite_add_tcase(s, strerror);

  strtok = tcase_create("strtok");
  tcase_add_test(strtok, strtok_testing);
  suite_add_tcase(s, strtok);

  to_upper = tcase_create("to_upper");
  tcase_add_test(to_upper, to_upper_testing);
  suite_add_tcase(s, to_upper);

  to_lower = tcase_create("to_lower");
  tcase_add_test(to_lower, to_lower_testing);
  suite_add_tcase(s, to_lower);

  insert = tcase_create("insert");
  tcase_add_test(insert, insert_testing);
  suite_add_tcase(s, insert);

  trim = tcase_create("trim");
  tcase_add_test(trim, trim_testing);
  suite_add_tcase(s, trim);

  return s;
}