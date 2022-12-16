#include "s21_string.h"

char *s21_strcat(char *dest, const char *src) {
  int start = s21_strlen(dest);
  int end = s21_strlen(src);
  for (int i = 0; i < (start + end); i++) {
    dest[start+i] = src[i];
  }
  return dest;
}
