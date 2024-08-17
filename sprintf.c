#include <stdlib.h>

#include "../s21_string.h"
#include "../shared/utils.h"
#include "./sprintf_strategy.h"

int isNum(char specifier) { return !!s21_strchr("douxXp", specifier); }

int isFloat(char specifier) { return !!s21_strchr("eEfgG", specifier); }

void precisionInit(TStrFormatParse *PFormat, va_list *args) {
  PFormat->precision =
      PFormat->precisionStar ? va_arg(*args, int) : PFormat->precision;
  if (PFormat->precision < 0) {
    if (isNum(PFormat->type)) {
      PFormat->precision = 1;
      if (PFormat->type == 'p') PFormat->precision = -1;
    } else if (isFloat(PFormat->type))
      PFormat->precision = 6;
  }
}

void widthInit(TStrFormatParse *PFormat, va_list *args) {
  PFormat->width = PFormat->widthStar ? va_arg(*args, int) : PFormat->width;
}

void numPrecision(TGetValueFromArg *arg, TStrFormatParse *PFormat) {
  int isNegative = arg->value[0] == '-';
  int length = arg->length - isNegative;
  int zeroCount = PFormat->precision - length;
  if (PFormat->flags->zero && !PFormat->flags->minus)
    zeroCount += PFormat->width - 1 - isNegative;
  char *buff = repeat('0', zeroCount);
  if (buff) {
    if (isNegative) {
      arg->value[0] = '0';
      buff[0] = '-';
    }
    arg->value = prepend(arg->value, buff);
    arg->length = s21_strlen(arg->value);
    free(buff);
  }
}

void sprintfFlagHandle(TGetValueFromArg *arg, TStrFormatParse *PFormat) {
  int isCorrectFlags = !!s21_strchr("dfpeEgG", PFormat->type) &&
                       (PFormat->flags->plus || PFormat->flags->space);
  int isNegative = arg->value[0] == '-';
  int hasDot = !!s21_strchr(arg->value, '.');
  int isCorrectFlagDot = !!s21_strchr("aAeEfFgG", PFormat->type);

  if (PFormat->flags->jail || PFormat->type == 'p') {
    if (!hasDot && isCorrectFlagDot)
      arg->value = append(arg->value, ".");
    else if (PFormat->type == 'o')
      arg->value = prepend(arg->value, "0");
    else if (PFormat->type == 'x' || PFormat->type == 'p')
      arg->value = prepend(arg->value, "0x");
    else if (PFormat->type == 'X')
      arg->value = prepend(arg->value, "0X");
  }

  if (!isNegative && isCorrectFlags)
    arg->value = prepend(arg->value, PFormat->flags->plus ? "+" : " ");

  arg->length = s21_strlen(arg->value);
}

void sprintfWidthHandle(TGetValueFromArg *arg, TStrFormatParse *PFormat) {
  arg->value = strWidth(
      arg->value, PFormat->width,
      !PFormat->flags->minus && PFormat->flags->zero && PFormat->type != 'c'
          ? '0'
          : ' ',
      PFormat->flags->minus ? 1 : 0);
  arg->length = s21_strlen(arg->value);
}

int printProccess(char *str, TStrFormatParse *PFormat, va_list *args,
                  TGetValueFromArgStrategy getValueFromArg) {
  widthInit(PFormat, args);
  precisionInit(PFormat, args);
  TGetValueFromArg arg = getValueFromArg(PFormat, args);

  if (isNum(PFormat->type)) numPrecision(&arg, PFormat);
  sprintfFlagHandle(&arg, PFormat);
  if ((!(PFormat->flags->zero && !PFormat->flags->minus) ||
       !isNum(PFormat->type)) &&
      PFormat->type != '%')
    sprintfWidthHandle(&arg, PFormat);

  s21_strncat(str, arg.value, arg.length);

  freeGetValueFromArg(&arg);
  return arg.length;
}

int s21_sprintf(char *str, const char *format, ...) {
  if (format == S21_NULL) {
    return -1;
  }

  int result = 0;
  va_list args;
  va_start(args, format);
  str[0] = '\0';

  for (int i = 0; format[i] != '\0'; i++) {
    int isFormat = format[i] == '%';
    if (isFormat) {
      TStrFormatParse *PFormat = createFormatParse();
      strFormatParser((char *)&format[i], PFormat);

      if (!PFormat->isIgnore) {
        result +=
            printProccess(str, PFormat, &args,
                          getValueFromArgStrategyBySpecifier(PFormat->type));

        i += PFormat->formatLength;
      }

      freeFormatParse(PFormat);
    } else {
      char buff[] = {format[i]};
      s21_strncat(str, buff, 1);
      result++;
    }
  }

  va_end(args);
  return result;
}