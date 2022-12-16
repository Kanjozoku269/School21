#include "s21_string.h"

void *s21_memset (void *dest, int c, s21_size_t n) {
    char *buffer;
    buffer = (char *)dest;
    if (dest != s21_NULL) {
        s21_size_t i = 0;
        while (i < n) {
            buffer[i] = c;
            i++;
        }
    }
    return dest;
}
