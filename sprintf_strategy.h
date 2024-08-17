#include <stdarg.h>

#include "../shared/str_format_parser.h"

typedef struct {
  char* value;
  int length;
} TGetValueFromArg;

typedef TGetValueFromArg (*TGetValueFromArgStrategy)(TStrFormatParse* PFormat,
                                                     va_list* args);

TGetValueFromArgStrategy getValueFromArgStrategyBySpecifier(char specifier);
void freeGetValueFromArg(TGetValueFromArg* arg);