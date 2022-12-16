#include "s21_string.h"

char *s21_strstr(const char* str1, const char *str2) {
    char *s = (char*) str1;
    int siz = s21_strlen(str2);
    int f = 1;
    char* res = s21_NULL;
    while (*s != '\0' && f == 1) {
        if (s21_strncmp(s, str2, siz) == 0) {
            f = 0;
            res = s;
        } else {
            s++;
        }
    }
    return res;
}