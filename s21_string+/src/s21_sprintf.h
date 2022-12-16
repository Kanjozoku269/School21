#include "s21_string.h"

#define CHAR_PATTERN 6000

typedef long unsigned s21_size_t;

typedef struct info {
  va_list args;
  int width;
  int precision;
  int hex_size;
  int zero_padding;
  int point;
  int dash;
  int total_length;
  int sign;
  int is_zero;
  int space;
  int hash;
  int j_save_format;
  int flag_f_float;
  int flag_o;
  int flag_e;
  int flag_u;
  int flag_h;
  int flag_l;
  int flag_s;
  int flag_dash;
  int flag_zero;
  int flag_float_zero;
  int exp;
  char full_buf[CHAR_PATTERN];
} s_info;

char *itoa(long long int value, char *result, int base);
char *itoa_u(unsigned long long int value, char *result, int base);
int s21_sprintf(char *str, const char *format, ...);
void wparg_help(s_info *ints);
char *s_strncat(char *dest, const char *src, s21_size_t n);
void print_res(s_info *ints, const char *str, int temp);
int print_format(s_info *ints, const char *format, int temp);
void print_unsigned(s_info *ints);
void point_o(s_info *ints, unsigned long long numb, char o);
void print_numb(s_info *ints);
void print_char(s_info *ints);
void print_str(s_info *ints);
void print_pointer(s_info *ints);
void print_hex(s_info *ints);
void print_hexup(s_info *ints);
void print_per(s_info *ints);
void print_float(s_info *ints);
int check_format(const char *format, int temp, s_info *ints);
int check_format_letter(const char *format, int temp, s_info *ints);
int check_format_letter_2(const char *format, int temp, s_info *ints);
int check_percision(s_info *ints, const char *format, int temp);
int check_point(s_info *ints, const char *format, int temp);
int check_wp(s_info *ints, const char *format, int temp);
int check_wparg(s_info *ints, const char *format, int temp);
int n_len(int n);
void s21_sprintf_g(s_info *ints);

void flag_exp(s_info *ints);
void ftoa(long double n, char *res, s_info *ints);
void reverse(char *str, int len);
int intToStr(long long int x, char str[], int d);
unsigned int un_len(unsigned int n);
void width_full(s_info *ints, int flag);
void prec_ful(s_info *ints);
int put_str(s_info *ints, char *s);
void scanndase(s_info *ints, unsigned long long numb);
void point_b(s_info *ints, unsigned long long numb, char x);
void put(int n, s_info *ints);
void putnbr(unsigned n, s_info *ints);
void litle_if(s_info *ints, long long int *numb);
void else_if(s_info *ints, long long int *numb);
void scanndase_o(s_info *ints, unsigned long long numb);
int str_else(char *s, s_info *ints);
void hexup_help(s_info *ints, unsigned int hexup);
void hex_help(s_info *ints, unsigned int hexal);
void numb_if(long long int numb, s_info *ints);
char *s_strcat(char *dest, const char *src);
void unsint_if(unsigned int uns, s_info *ints);
int check_help(s_info *ints, const char *format, int temp);
size_t s21strlen(const char *str);

// + в F и в E
// // пробел в F и не надо в  D
// // доработать G

// int main() {
//   char s21_buffer[256] = {0};
//   char buffer[256] = {0};
//   int w = 0;
//   int l = 0;
//   sprintf(buffer, "%1.3g %01g%# *.*g %n", 10009000., 0.003, -10, 5,
//           0.000074047471, &w);
//   s21_sprintf(s21_buffer, "%1.3g %01g %# *.*g %n", 10009000., 0.003, -10,
//               5, 0.000074047471, &l);
//   printf("%s\n", s21_buffer);
//   printf("%s\n", buffer);

//     printf("%d\n", w);
//   printf("%d\n", l);

//   return 0;
// }