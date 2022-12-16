#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  int i = 0;
  while (str[i] && str[i] != (char)c) {
      i++;
  }
  while (str[i] == '\0' && c != 0) {
      return (NULL);
  }
  return ((char *)(str + i));
}
