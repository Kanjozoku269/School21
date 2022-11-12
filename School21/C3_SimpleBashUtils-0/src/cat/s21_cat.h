#ifndef SRC_S21_CAT_H
#define SRC_S21_CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

static struct option long_options[] = {
    {"number-nonblank", 0, 0, 'b'},
    {"number", 0, 0, 'n'},
    {"squeeze-blank)", 0, 0, 's'},
};

int flagb = 0, flagn = 0, flage = 0, flagv = 0, flags = 0, flagt = 0, num = 0, numc = 0;
int countSym = 0, countS = 0, newStr = 0, countT = 0, countV = 0;

FILE *file;

char c, oldc, flag;

void switchs(char flag, int argc, char *argv[]) {
  if (argc != 1) {
    while ((flag = getopt_long(argc, argv, "+bneEstTv", long_options, NULL)) !=
           EOF) {
      switch (flag) {
        case 'b':
          flagb++;  // b нумерация не пустых строк
          break;
        case 'n':
          flagn++;  // n нумерация всех строк
          break;
        case 'e':
        case 'E':
          flage++;  // e печатает $ в конце строк
          flagv++;
          break;
        case 's':
          flags++;  // s сжимает пустые строки
          break;
        case 't':
        case 'T':
          flagt++;  // t превращает табы в ^I
          flagv++;
          break;
        case 'v':
          flagv++;  // v нечитабельный символ меняет на ^
          break;
        default:
          printf("usage: cat [-benstuv] [file ...]");
          exit(1);
      }
    }
  }
}
void open_file(char *argv[]) {
  
    if ((file = fopen(argv[optind], "r")) == NULL) {
      perror("NO FILE");
      exit(1);
    }
}

void flag_s(int newStr, int countSym, int *countS, char c) {
  if (flags) {
    if (newStr == 1 && countSym == 1) {
      newStr = 2;
      *countS = 1;
    }
    if (newStr < 3) {
      *countS = 1;
      if (c != '\n') newStr = 0;
    } else if (c != '\n') {
      newStr = 0;
      *countS = 1;
    }
  }
}

void flag_b(int flagb, int flags, int* countS) {
  if (flagb) {
    if (!flags && (numc == 1 || oldc == '\n') && c != '\n') {
      printf("%6.d\t", num);
      num++;
    }
    if (flags && (oldc == '\n' || numc == 1)) {
      if (c != '\n' && *countS) {
        printf("%6.d\t", num);
        num++;
      }
    }
  }
}
void flag_v(int flagv, char c, int *countV) {
  if (flagv) {
    if (c >= 0 && c != 9 && c != 10 && c < 32) {
      printf("^%c", c + 64);
      *countV = 1;
    } else if (c == 127) {
      printf("^?");
      *countV = 1;
    }
  }
}

void flag_t(int flagt, int *countT) {
  if (flagt) {
    if (c == 9) *countT = 1;
  }
}

void flag_e(int flage, int *countS) {
  if (flage) {
    if (!flage && c == '\n') {
      printf("$");
    } else if (*countS && c == '\n') {
      printf("$");
    }
  }
}

void flag_n(int flagn, int flagb, int *countS) {
  if (flagn && !flagb) {
    if ((oldc == '\n' || numc == 1) && !flags) {
      printf("%6.d\t", num);
      num++;
    } else if (flags && (oldc == '\n' || numc == 1)) {
      if (*countS) {
        printf("%6.d\t", num);
        num++;
      }
    }
  }
}

void output(int c, int *countS, int *countT, int *countV) {
  if (flags && countS) {
    if (*countT) {
      printf("^I");
      *countS = 0;
      *countT = 0;
    } else if (*countV) {
      *countV = 0;
    } else {
      printf("%c", c);
      *countS = 0;
    }
  } else if (!flags) {
    if (*countT) {
      printf("^");
      printf("I");
      *countT = 0;
    } else if (*countV) {
      *countV = 0;
    } else {
      printf("%c", c);
    }
  }
}

void global_f1(int argc, char *argv[]) {
  while (optind < argc) {
    open_file(argv);  // Функция открытия файла(ов)
    while ((c = getc(file)) != EOF) {
      // место под флаги
      flag_s(newStr, countSym, &countS, c);
      flag_b(flagb, flags, &countS);
      flag_v(flagv, c, &countV);
      flag_t(c, &countT);
      flag_e(flage, &countS);
      flag_n(flagn, flagb, &countS);
      
      // output f
      output(c, &countS, &countT, &countV);
      oldc = c;
      numc++;
    }  // sbvten
    optind++;
    fclose(file);
    num = 1;
  }
}


//void flag_n() {

//}
void glob_f(int argc, char *argv[]) {
  switchs(flag, argc, argv);  // Функция парсера
  global_f1(argc, argv); 
}
#endif // SRC_S21_CAT_H_