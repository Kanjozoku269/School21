#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
   unsigned char s1, s2;
   while (n) {
    s1 = *str1++;
    s2 = *str2++;
    if (s1 == '\0' || (s1 != s2)) return s1 - s2;
    n--;
   } return 0;
}