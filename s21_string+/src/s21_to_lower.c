#include "s21_string.h"

void *s21_to_lower(const char *str) {
  int str_len = s21_strlen(str);
  char *res_str = s21_NULL;
  res_str = (char *)malloc(sizeof(char *) * str_len);

  if (res_str) {
    s21_strcpy(res_str, (char *)str);
    for (int i = 0; i < str_len; i++)
      if (res_str[i] >= 65 && res_str[i] <= 90) {
        res_str[i] = res_str[i] + 32;
      }
  }
  return res_str;
}