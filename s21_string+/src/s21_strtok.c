#include "s21_string.h"

// Разбивает строку str на ряд токенов, разделенных delim
char *s21_strtok(char *str, const char *delim) {
  static int next_null, tok;
  static s21_size_t ind;
  static char *max_ptr;
  static char *addr;
  if (str) {
    tok = 1;
    ind = 0, next_null = 0;
    addr = str + s21_strspn(str, delim);
    max_ptr = str + s21_strlen(str);
  }
  char *res = s21_NULL;
  if (!(addr >= max_ptr || next_null)) {
    int non_delim = 1;
    for (int i = 0; addr[i]; i++) {
      s21_size_t step = s21_strspn(addr + i, delim);
      if (step) {
        non_delim = 0;
        for (s21_size_t j = i; j < i + step; j++) addr[j] = '\0';

        ind = step + i;
        break;
      }
    }
    if (tok == 1 && non_delim) next_null = 1;
    res = addr;
    addr += ind;  
  }
  ++tok;
  return res;
}
