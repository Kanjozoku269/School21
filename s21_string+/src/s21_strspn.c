#include "s21_string.h"

// Вычисляет длину начального сегмента str1, который полностью состоит из символов, не входящих в str2.

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t i = 0;
  while (str1[i] && s21_strchr(str2, str1[i])) i++;
  return i;
}
