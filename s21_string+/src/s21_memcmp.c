#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    unsigned char mem1, mem2;
    int res = 0;
    for ( ; n-- ; str1++, str2++) {
	mem1 = *(unsigned char *)str1;
	mem2 = *(unsigned char *)str2;
	if ( mem1 != mem2) {
	    return (mem1-mem2);
	}
}
return res;
}
