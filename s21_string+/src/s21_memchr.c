#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned const char *buf;
  s21_size_t i;
  buf = str;
  i = 0;
  while (i < n) {
    if (buf[i] == (unsigned char)c) {
      return ((void *)(buf + i));
    }
    i++;
  }
  return (NULL);
}