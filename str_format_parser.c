#include "./str_format_parser.h"

#include <stdlib.h>

#include "../s21_string.h"

typedef int (*pipeFunc)(char*, TStrFormatParse*);

int isNumber(char sym) { return !!s21_strchr("1234567890", sym); }

int getIntFromCharsSize(char* str) {
  int result = 0;

  for (char* tmp = str; *tmp != '\0' && isNumber(*tmp); tmp++, result++)
    ;

  return result;
}

int convertCharsToInt(char* sym) {
  int result = 0;
  int size = getIntFromCharsSize(sym);

  for (char* tmp = sym; size; size--, tmp++) {
    result += *tmp - '0';
    if (size - 1) result *= 10;
  }

  return result;
}

void parseFlag(TStrFormatFlagsInfo* flags, char sym) {
  switch (sym) {
    case '+':
      flags->plus = 1;
      break;
    case '-':
      flags->minus = 1;
      break;
    case '#':
      flags->jail = 1;
      break;
    case ' ':
      flags->space = 1;
      break;
    case '0':
      flags->zero = 1;
      break;
  }
}

int parseFlags(char* format, TStrFormatParse* strFormatParse) {
  int result = 0;

  for (char* tmp = format; !!s21_strchr("-+#0 ", *tmp) && *tmp != '\0'; tmp++) {
    parseFlag(strFormatParse->flags, *tmp);
    result++;
  }

  return result;
}

int widthParse(char* format, TStrFormatParse* strFormatParse) {
  int result = 0;

  if (isNumber(*format)) {
    strFormatParse->width = convertCharsToInt(format);
    int size = getIntFromCharsSize(format);
    result += size;
  } else if (*format == '*') {
    strFormatParse->widthStar = 1;
    result++;
  }

  return result;
}

int precisionParse(char* format, TStrFormatParse* strFormatParse) {
  int result = 0;

  if (*format == '.') {
    result++;
    if (*(format + result) == '*') {
      strFormatParse->precisionStar = 1;
      result++;
    } else {
      strFormatParse->precision = convertCharsToInt(format + result);
      int size = getIntFromCharsSize(format + result);
      result += size;
    }
  }

  return result;
}

int lengthParse(char* format, TStrFormatParse* strFormatParse) {
  int result = 0;

  if (!!s21_strchr("lhL", *format)) {
    strFormatParse->length = *format;
    result++;
  }

  return result;
}

int strFormatParser(char* format, TStrFormatParse* strFormatParse) {
  pipeFunc funcs[4] = {parseFlags, widthParse, precisionParse, lengthParse};
  char* tmp = format + 1;
  int length = 0;

  for (int i = 0; i < 4; i++) {
    int size = funcs[i](tmp, strFormatParse);
    length += size;
    tmp += size;

    if (*tmp == '\0') {
      strFormatParse->isIgnore = 1;
      return 0;
    }
  }

  if (!!s21_strchr("cdfsugGeExXop%", *tmp)) {
    strFormatParse->type = *tmp;
    strFormatParse->formatLength = length + 1;
  } else {
    strFormatParse->isIgnore = 1;
  }

  return 0;
}

TStrFormatParse* createFormatParse() {
  TStrFormatFlagsInfo* flags = malloc(sizeof(TStrFormatFlagsInfo));
  flags->jail = 0;
  flags->zero = 0;
  flags->space = 0;
  flags->minus = 0;
  flags->plus = 0;
  TStrFormatParse* result = malloc(sizeof(TStrFormatParse));
  result->flags = flags;
  result->width = 0;
  result->precision = -1;
  result->length = 0;
  result->widthStar = 0;
  result->precisionStar = 0;
  result->type = 0;
  result->isIgnore = 0;
  result->formatLength = 0;

  return result;
}

void freeFormatParse(TStrFormatParse* formatParse) {
  free(formatParse->flags);
  free(formatParse);
}