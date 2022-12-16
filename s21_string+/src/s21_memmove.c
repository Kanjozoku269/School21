#include "s21_string.h"

void *s21_memmove (void *dest, const void *src, s21_size_t n) {
    unsigned char *destptr = (unsigned char *)dest;
    unsigned char *srcptr = (unsigned char *)src;
if (destptr < srcptr)
    while (n--)
        *destptr++ = *srcptr++;
else {
    unsigned char *lasts = srcptr + (n-1);
    unsigned char *lastd = destptr + (n-1);
    while (n--)
        *lastd-- = *lasts--;
    }
    return dest;
}