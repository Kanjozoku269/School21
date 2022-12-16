#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
    char *s1 = (char*)str1;
    char *s2 = (char*)str2;
    int s = s21_strlen(str2);
    int flag = 1;
    char *result = NULL;
    while (*s1 != '\0' && flag == 1) {
        for (int i = 0; s > i && flag == 1; i++) {
            if (*s1 == s2[i]) {
                flag = 0;
                result = s1;
            }
        }
        s1++;
    }
    return result;
}