#include "s21_string.h"


char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  int start = s21_strlen(dest);
  unsigned int i = 0;
  for ( ; i < n; i++) {
    dest[start+i] = src[i];
  }
  dest[start + i] = '\0';
  return dest;
}
