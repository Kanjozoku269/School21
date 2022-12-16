#include "s21_string.h"

void *s21_insert(const char *src, const char *str, size_t start_index) {
  int src_len = s21_strlen(src);
  int str_len = s21_strlen(str);
  int total_len = src_len + str_len;

  if ((int)start_index > src_len || (int)start_index < 0) return s21_NULL;

  char *res_str = (char *)malloc(sizeof(char *) * (total_len));

  if (res_str) {
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < (int)start_index) {
      res_str[i] = src[i];
      i++;
      k++;
    }

    while (i < (int)start_index + str_len) {
      res_str[i] = str[j];
      i++;
      j++;
    }

    while (i < total_len) {
      res_str[i] = src[k];
      i++;
      k++;
    }

    res_str[i] = '\0';
  }

  return res_str;
}
