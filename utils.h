char* s21_itoa(long int value, char* buffer, int base);
char* s21_ftoa(long double value, char* buff, int afterpoint, int isScience);
char* s21_uitoa(unsigned long int value, char* buffer, int base);
char* repeat(char sym, int count);
char* append(char* dest, char* append);
char* prepend(char* dest, char* append);
char* strWidth(char* str, int width, char sym, int isRight);
int getldLength(long double x);