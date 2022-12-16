#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *arr;
  int inerror = 0;
  if (src && trim_chars != s21_NULL) {
    arr = (char *)calloc((s21_strlen(src) + 1), sizeof(char));
    if (arr == s21_NULL) inerror++;
    s21_strcat(arr, src);
    int inbreak = 0;
    for (s21_size_t i = 0; i < s21_strlen(src); i++) {
      for (s21_size_t j = 0; j < s21_strlen(trim_chars); j++) {
        if (trim_chars[0] == '\0') {
          inerror++;
        }
        if (src[i] == trim_chars[j]) {
          int h = 0;
          while (arr[h]) {
            arr[h] = arr[h + 1];
            h++;
          }
          break;
        }
        if (j == s21_strlen(trim_chars) - 1 &&
            src[i] != trim_chars[s21_strlen(trim_chars)]) {
          inbreak = 1;
        }
      }
      if (inbreak) break;
    }

    for (size_t i = s21_strlen(arr) - 1; i > 0; i--) {
      inbreak = 0;
      if (arr[0] == '\0') {
        inbreak = 1;
      }
      for (size_t j = 0; j < s21_strlen(trim_chars); j++) {
        if (trim_chars[0] == '\0') {
          inerror++;
        }
        if (arr[i] == trim_chars[j]) {
          arr[i] = '\0';
          break;
        }
        if (j == s21_strlen(trim_chars) - 1 &&
            src[i] != trim_chars[s21_strlen(trim_chars)]) {
          inbreak = 1;
        }
      }
      if (inbreak) break;
    }
  } else {
    inerror++;
  }
  return inerror > 0 ? s21_NULL : (void *)arr;
}
