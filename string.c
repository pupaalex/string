#include "../s21_string.h"
#include "./strerror.h"

s21_size_t s21_strlen(const char *str) {
  s21_size_t result = 0;
  for (char *tmp = (char *)str; *tmp != '\0'; tmp++, result++) {
  }
  return result;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *ptr = dest + s21_strlen(dest);

  for (; n && *src != '\0'; ptr++, src++, n--) *ptr = *src;
  *ptr = '\0';

  return dest;
}

char *s21_strchr(const char *str, int c) {
  char *temp = (char *)str;
  void *res = ((char)c == '\0') ? "\0" : S21_NULL;
  s21_size_t i = 0;
  while (*(temp + i) != '\0' && *(temp + i) != c) i++;
  if (*(temp + i) != '\0') res = temp + i;
  return res;
}

char *s21_strrchr(const char *str, int c) {
  const char *res = S21_NULL;
  if (str != S21_NULL) {
    while (*str != '\0') {
      if (*str == c) {
        res = str;
      }
      str++;
    }
  }
  if (*str == c) {
    res = (char *)str;
  }
  return (char *)res;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  for (; n && *str1 && (*str1 == *str2); str1++, str2++, n--) {
  }
  return !n ? 0 : (*(char *)str1 - *(char *)str2);
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i;
  for (i = 0; i < n && src[i] != '\0'; i++) dest[i] = src[i];
  for (; i < n; i++) dest[i] = '\0';
  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t result = 0;

  for (char *tmp = (char *)str1, k = 0; *tmp != '\0' && !k; tmp++)
    if (!s21_strchr(str2, *tmp))
      result++;
    else
      k = 1;

  return result;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = S21_NULL;

  for (; *haystack != '\0' && !result; haystack++) {
    char *tmp1 = (char *)haystack, *tmp2 = (char *)needle;
    for (int isIdenty = 1; tmp1 && tmp2 && isIdenty && *haystack == *needle;) {
      if (*tmp1 != *tmp2 || *tmp1 == '\0') isIdenty = 0;
      if (isIdenty) tmp1++, tmp2++;
    }
    result = *tmp2 == '\0' ? (char *)haystack : S21_NULL;
  }

  return result;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *ptr1 = (unsigned char *)dest;
  unsigned char *ptr2 = (unsigned char *)src;
  for (s21_size_t i = 0; i < n; i++) {
    *ptr1 = *ptr2;
    ptr1++;
    ptr2++;
  }
  return dest;
}

s21_size_t s21_strspn(const char *haystack, const char *entries) {
  s21_size_t result = 0;
  s21_size_t haystack_len = s21_strlen(haystack);
  int stop = 0;
  for (s21_size_t i = 0; i < haystack_len && !stop; ++i) {
    if (s21_strchr(entries, haystack[i]) != S21_NULL) {
      ++result;
    } else {
      stop = 1;
    }
  }

  return result;
}

char *s21_strtok(char *str, const char *delim) {
  static char *tek = S21_NULL;
  char *res = S21_NULL;
  if (str) {
    tek = str;
    while (*tek && s21_strchr(delim, *tek)) tek++;
    if (*tek) {
      res = tek;
      while (*tek && !s21_strchr(delim, *tek)) {
        tek++;
      }
      if (*tek) {
        *tek++ = 0;
      }
    } else {
      tek = S21_NULL;
    }
  }
  return res;
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *ptr = (unsigned char *)str;
  const void *result = S21_NULL;
  for (s21_size_t i = 0; i < s21_strlen(str) && i < n; i++) {
    if (*ptr == (unsigned char)c) {
      result = (str + i);
      break;
    }
    ptr++;
  }
  return (void *)result;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  unsigned char *temp1 = (unsigned char *)str1;
  unsigned char *temp2 = (unsigned char *)str2;

  for (s21_size_t i = 0; i < n; ++i) {
    if (temp1[i] != temp2[i]) {
      return temp1[i] - temp2[i];
    }
  }

  return 0;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  for (unsigned char *tmp = str; n > 0; n--, tmp++) *tmp = (unsigned char)c;
  return str;
}

char *s21_strerror(int errnum) {
  char *res = S21_NULL;
  static char error[150];
  if (errnum >= 0 || errnum < S21_ERRLIST_SIZE) {
    res = (char *)s21_sys_errlist[errnum];
  } else {
    s21_memset(res, '\0', 100);
    s21_sprintf(res, "Unknown error %d", errnum);
    res = error;
  }
  return res;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  const char *result = S21_NULL;
  for (s21_size_t i = 0; i < s21_strlen(str1) && !result; i++) {
    for (s21_size_t j = 0; j < s21_strlen(str2); j++) {
      if (str1[i] == str2[j]) result = (str1 + i);
    }
  }
  return (char *)result;
}

void *s21_to_upper(const char *str) {
  char *res = S21_NULL;
  for (s21_size_t i = 0; i < s21_strlen(str); i++) {
    if (res == S21_NULL) res = (char *)str;
    if (str[i] >= 'a' && str[i] <= 'z')
      res[i] = str[i] - 32;
    else
      res[i] = str[i];
  }
  return res;
}

void *s21_to_lower(const char *str) {
  char *res = S21_NULL;
  for (s21_size_t i = 0; i < s21_strlen(str); i++) {
    if (res == S21_NULL) res = (char *)str;
    if (str[i] >= 'A' && str[i] <= 'Z')
      res[i] = str[i] + 32;
    else
      res[i] = str[i];
  }
  return res;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  int check = 0;
  int len = s21_strlen(str) + s21_strlen(src);
  char *res = S21_NULL;
  char res2[len];

  if (start_index < s21_strlen(src) + 1) {
    for (int i = 0; i <= len; i++) {
      if (res == S21_NULL) res = res2;
      if (i == (int)start_index) {
        check = 1;
        for (s21_size_t j = 0; j < s21_strlen(str); j++) res[i + j] = str[j];
        i = i + s21_strlen(str) - 1;
      } else {
        if (check)
          res[i] = src[i - s21_strlen(str)];
        else
          res[i] = src[i];
      }
    }
  }
  res[len] = '\0';
  return res;
}

void *s21_trim(const char *src, const char *trim_chars) {
  int badSym = 0;
  s21_size_t len = s21_strlen(src);
  char *res = S21_NULL;
  char res2[len];
  int propusk = 0;
  for (s21_size_t i = 0; i <= len; i++) {
    badSym = 0;
    if (res == S21_NULL) res = res2;
    for (s21_size_t j = 0; j < s21_strlen(trim_chars) && !badSym; j++) {
      if (src[i] == trim_chars[j]) badSym = 1;
    }
    if (!badSym)
      res[i - propusk] = src[i];
    else
      propusk++;
  }
  return res;
}