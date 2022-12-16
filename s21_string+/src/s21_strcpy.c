#include "s21_string.h"

char *s21_strcpy(char *dest, const char *src) {
  int srcptrLength = s21_strlen(src);

  for (int x = 0; x <= srcptrLength; x += 1) {
    dest[x] = src[x];
  }

  return dest;
}