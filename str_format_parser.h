typedef struct {
  int jail;
  int zero;
  int minus;
  int plus;
  int space;
} TStrFormatFlagsInfo;

typedef struct {
  TStrFormatFlagsInfo* flags;
  int width;
  int widthStar;
  int precision;
  int precisionStar;
  char length;
  char type;
  int isIgnore;
  int formatLength;
} TStrFormatParse;

int strFormatParser(char* format, TStrFormatParse* strFormatParse);
TStrFormatParse* createFormatParse();
void freeFormatParse(TStrFormatParse* formatParse);
