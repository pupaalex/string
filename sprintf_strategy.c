#include "./sprintf_strategy.h"

#include <stdlib.h>
#include <wchar.h>

#include "../s21_string.h"
#include "../shared/utils.h"

void to_lower_di(char* str) { s21_to_lower(str); }

TGetValueFromArg DecimalStrategy(TStrFormatParse* PFormat, va_list* args) {
  TGetValueFromArg result = {S21_NULL, 0};
  char buff[30];
  if (PFormat->length == 'h')
    s21_itoa((short)va_arg(*args, int), buff, 10);
  else if (PFormat->length == 'l')
    s21_itoa(va_arg(*args, long), buff, 10);
  else
    s21_itoa(va_arg(*args, int), buff, 10);
  s21_size_t length = s21_strlen(buff);
  result.value = calloc(length + 1, sizeof(char));
  result.value[0] = '\0';
  s21_strncpy(result.value, buff, length);
  result.length = length;
  return result;
}

TGetValueFromArg UnsignedDecimalStrategy(TStrFormatParse* PFormat,
                                         va_list* args) {
  TGetValueFromArg result = {S21_NULL, 0};
  char buff[30];
  if (PFormat->length == 'h')
    s21_uitoa((unsigned short)va_arg(*args, unsigned int), buff, 10);
  else if (PFormat->length == 'l')
    s21_uitoa(va_arg(*args, unsigned long int), buff, 10);
  else
    s21_uitoa(va_arg(*args, unsigned int), buff, 10);
  s21_size_t length = s21_strlen(buff);
  result.value = calloc(length + 1, sizeof(char));
  result.value[0] = '\0';
  s21_strncpy(result.value, buff, length);
  result.length = length;
  return result;
}

TGetValueFromArg CharStrategy(TStrFormatParse* PFormat, va_list* args) {
  TGetValueFromArg result = {S21_NULL, 0};

  if (PFormat->length == 'l') {
    wint_t arg = va_arg(*args, wint_t);
    result.value = calloc(2, sizeof(wint_t));
    wint_t temp[2] = {arg, L'\0'};
    wcstombs(result.value, (wchar_t*)temp, sizeof(wint_t));
    result.length = sizeof(wint_t);
  } else {
    char arg = va_arg(*args, int);
    result.value = calloc(2, sizeof(char));
    result.value[0] = arg;
    result.value[1] = '\0';
    result.length = 1;
  }
  return result;
}

void stringStrategyNullHandler(TGetValueFromArg* result,
                               TStrFormatParse* PFormat) {
  if (PFormat->precision >= 6 || PFormat->precision < 0) {
    result->value = calloc(6 + 1, sizeof(char));
    s21_strncat(result->value, "(null)", 6);
    result->length = 6;
  } else {
    result->value = calloc(1, sizeof(char));
    result->value[0] = '\0';
    result->length = 0;
  }
}

TGetValueFromArg StringStrategy(TStrFormatParse* PFormat, va_list* args) {
  TGetValueFromArg result = {S21_NULL, 0};

  if (PFormat->length == 'l') {
    wchar_t* arg = va_arg(*args, wchar_t*);
    if (arg != S21_NULL) {
      s21_size_t wcharSize = sizeof(wchar_t);
      s21_size_t length = PFormat->precision < 0
                              ? wcslen(arg)
                              : (s21_size_t)(PFormat->precision / wcharSize);
      result.value = calloc(length + 1, sizeof(wchar_t));
      s21_size_t byteLength = wcharSize * length;
      wcstombs(result.value, arg, byteLength);
      result.length = byteLength;
    } else
      stringStrategyNullHandler(&result, PFormat);
  } else {
    char* arg = va_arg(*args, char*);
    if (arg != S21_NULL) {
      s21_size_t length = PFormat->precision < 0
                              ? s21_strlen(arg)
                              : (s21_size_t)PFormat->precision;
      result.value = calloc(length + 1, sizeof(char));
      s21_strncat(result.value, arg, length);
      result.length = length;
    } else
      stringStrategyNullHandler(&result, PFormat);
  }

  return result;
}

TGetValueFromArg PercentStrategy(TStrFormatParse* PFormat, va_list* args) {
  (void)args;
  (void)PFormat;
  TGetValueFromArg result = {S21_NULL, 1};
  result.value = calloc(2, sizeof(char));
  result.value[0] = '%';
  result.value[1] = '\0';
  return result;
}

TGetValueFromArg FloatStrategy(TStrFormatParse* PFormat, va_list* args) {
  TGetValueFromArg result = {S21_NULL, 0};
  char buff[50];
  if (PFormat->length == 'L')
    s21_ftoa(va_arg(*args, long double), buff, PFormat->precision, 0);
  else
    s21_ftoa(va_arg(*args, double), buff, PFormat->precision, 0);
  s21_size_t length = s21_strlen(buff);
  result.value = calloc(length + 1, sizeof(char));
  result.value[0] = '\0';
  s21_strncpy(result.value, buff, length);
  result.length = length;
  return result;
}

TGetValueFromArg UnsignedUpperHexadecimalStrategy(TStrFormatParse* PFormat,
                                                  va_list* args) {
  TGetValueFromArg result = {S21_NULL, 0};
  char buff[30];
  if (PFormat->length == 'h')
    s21_uitoa((unsigned short)va_arg(*args, unsigned int), buff, 16);
  else if (PFormat->length == 'l')
    s21_uitoa(va_arg(*args, unsigned long int), buff, 16);
  else
    s21_uitoa(va_arg(*args, unsigned int), buff, 16);
  s21_size_t length = s21_strlen(buff);
  result.value = calloc(length + 1, sizeof(char));
  result.value[0] = '\0';
  s21_strncpy(result.value, buff, length);
  result.length = length;
  return result;
}

TGetValueFromArg UnsignedHexadecimalStrategy(TStrFormatParse* PFormat,
                                             va_list* args) {
  TGetValueFromArg result = UnsignedUpperHexadecimalStrategy(PFormat, args);
  to_lower_di(result.value);
  return result;
}

TGetValueFromArg UnsignedOctalStrategy(TStrFormatParse* PFormat,
                                       va_list* args) {
  TGetValueFromArg result = {S21_NULL, 0};
  char buff[100];
  if (PFormat->length == 'h')
    s21_uitoa((unsigned short)va_arg(*args, unsigned int), buff, 8);
  else if (PFormat->length == 'l')
    s21_uitoa(va_arg(*args, unsigned long int), buff, 8);
  else
    s21_uitoa(va_arg(*args, unsigned int), buff, 8);
  to_lower_di(buff);
  s21_size_t length = s21_strlen(buff);
  result.value = calloc(length + 1, sizeof(char));
  result.value[0] = '\0';
  s21_strncpy(result.value, buff, length);
  result.length = length;
  return result;
}

TGetValueFromArg PointerStrategy(TStrFormatParse* PFormat, va_list* args) {
  (void)PFormat;
  TGetValueFromArg result = {S21_NULL, 0};
  char buff[30];
  s21_uitoa((unsigned long int)va_arg(*args, void*), buff, 16);
  to_lower_di(buff);
  s21_size_t length = s21_strlen(buff);
  result.value = calloc(length + 1, sizeof(char));
  result.value[0] = '\0';
  s21_strncpy(result.value, buff, length);
  result.length = length;
  return result;
}

TGetValueFromArg ScienceUpperFloatStrategy(TStrFormatParse* PFormat,
                                           va_list* args) {
  TGetValueFromArg result = {S21_NULL, 0};
  char buff[50];
  if (PFormat->length == 'L')
    s21_ftoa(va_arg(*args, long double), buff, PFormat->precision, 1);
  else
    s21_ftoa(va_arg(*args, double), buff, PFormat->precision, 1);
  s21_size_t length = s21_strlen(buff);
  result.value = calloc(length + 1, sizeof(char));
  result.value[0] = '\0';
  s21_strncpy(result.value, buff, length);
  result.length = length;
  return result;
}

TGetValueFromArg ScienceFloatStrategy(TStrFormatParse* PFormat, va_list* args) {
  TGetValueFromArg result = ScienceUpperFloatStrategy(PFormat, args);
  to_lower_di(result.value);
  return result;
}

TGetValueFromArg ScienceShortUpperFloatStrategy(TStrFormatParse* PFormat,
                                                va_list* args) {
  TGetValueFromArg result = {S21_NULL, 0};
  char buff[50];
  int numLength = 0, isScience = 0;
  if (PFormat->length == 'L') {
    long double val = va_arg(*args, long double);
    numLength = getldLength(val);
    int currentLength = PFormat->precision - numLength;
    if (currentLength < 0) {
      s21_ftoa(val, buff, PFormat->precision - 1, 1);
      isScience = 1;
    } else
      s21_ftoa(val, buff, PFormat->precision - numLength, 0);
  } else {
    double val = va_arg(*args, double);
    numLength = getldLength(val);
    int currentLength = PFormat->precision - numLength;
    if (currentLength < 0) {
      isScience = 1;
      s21_ftoa(val, buff, PFormat->precision - 1, 1);
    } else
      s21_ftoa(val, buff, PFormat->precision - numLength, 0);
  }
  s21_size_t length = s21_strlen(buff);
  result.value = calloc(length + 1, sizeof(char));
  result.value[0] = '\0';
  s21_strncpy(result.value, buff, length);
  for (int i = length - 1, j = 1; j && i && !isScience; i--)
    if (result.value[i] == '0')
      result.value[i] = '\0';
    else
      j = 0;
  result.length = length;
  return result;
}

TGetValueFromArg ScienceShortFloatStrategy(TStrFormatParse* PFormat,
                                           va_list* args) {
  TGetValueFromArg result = ScienceShortUpperFloatStrategy(PFormat, args);
  to_lower_di(result.value);
  return result;
}

TGetValueFromArgStrategy getValueFromArgStrategyBySpecifier(char specifier) {
  TGetValueFromArgStrategy result = S21_NULL;

  switch (specifier) {
    case 'd':
      result = DecimalStrategy;
      break;
    case 'u':
      result = UnsignedDecimalStrategy;
      break;
    case 'c':
      result = CharStrategy;
      break;
    case 'f':
      result = FloatStrategy;
      break;
    case 's':
      result = StringStrategy;
      break;
    case '%':
      result = PercentStrategy;
      break;
    case 'p':
      result = PointerStrategy;
      break;
    case 'o':
      result = UnsignedOctalStrategy;
      break;
    case 'x':
      result = UnsignedHexadecimalStrategy;
      break;
    case 'X':
      result = UnsignedUpperHexadecimalStrategy;
      break;
    case 'e':
      result = ScienceFloatStrategy;
      break;
    case 'E':
      result = ScienceUpperFloatStrategy;
      break;
    case 'g':
      result = ScienceShortFloatStrategy;
      break;
    case 'G':
      result = ScienceShortUpperFloatStrategy;
      break;
  }

  return result;
}

void freeGetValueFromArg(TGetValueFromArg* arg) {
  if (arg->value) {
    free(arg->value);
  }
}
