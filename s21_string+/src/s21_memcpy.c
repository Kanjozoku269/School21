#include "s21_string.h"

void *s21_memcpy (void *dest, const void *src, s21_size_t n) {
    unsigned char *destptr = (unsigned char *)dest;
    unsigned char *srcptr = (unsigned char *)src;
    if (destptr != s21_NULL && srcptr != s21_NULL) {
        for (s21_size_t i = 0; i < n; i++) {
            destptr[i] = srcptr[i];
        }
   }
    return dest;
}