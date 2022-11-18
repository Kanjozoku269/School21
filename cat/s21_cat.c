#include "s21_cat.h"

int main(int argc, char *argv[]) {
  allOtherVars peremn = {1, 1, 0, 0, 1, 0, 0, 0, 0, 0, '0', '0'};
  flags allflags = {0};
  if (argc != 1) {
    int opt;
    while ((opt = getopt_long(argc, argv, "+bneEstTv", long_options, NULL)) !=
           EOF) {
      switchs(opt, &allflags);  // Функция парсер флагов
    }
  }
  while (optind < argc) {
    open_file(argv);  // Функция открытия файла(ов)
    while ((peremn.c = getc(file)) != EOF) {  // посимвольное считывание
      flag_s(&peremn, &allflags);  // удаление пустых строк
      flag_n(&peremn, &allflags);  // нумерация всех строк
      flag_b(&peremn, &allflags);  // нумерует только непустые строки
      flag_e(&peremn, &allflags);  // отображает символы конца строки как $
      flag_t(&peremn, &allflags);  // отображает табы как ^I
      flag_v(&peremn, &allflags);  // заменяет невидимые символы на a-z
      output(&peremn, &allflags);  // принты
      peremn.oldc = peremn.c;
      peremn.numc++;
    }
    optind++;
    fclose(file);
    peremn.num = 1;
  }
  return 0;
}

void switchs(char opt, flags *allflags) {
  switch (opt) {
    case 'b':
      allflags->flagb = (allflags->flagn = 0) + 1;
      allflags->flagb++;  // b нумерация не пустых строк
      break;
    case 'n':
      allflags->flagn = allflags->flagb ? 0 : 1;
      allflags->flagn++;  // n нумерация всех строк
      break;
    case 'e':
    case 'E':
      allflags->flage++;  // e печатает $ в конце строк
      allflags->flagv++;
      break;
    case 's':
      allflags->flags++;  // s сжимает пустые строки
      break;
    case 't':
    case 'T':
      allflags->flagt++;  // t превращает табы в ^I
      allflags->flagv++;
      break;
    case 'v':
      allflags->flagv++;  // v нечитабельный символ меняет на ^
      break;
    default:
      printf("usage: cat [-benstuv] [file ...]");
      error();
  }
}

void open_file(char *argv[]) {
  if ((file = fopen(argv[optind], "r")) == NULL) {
    perror("NO FILE");
    error();
  }
}

void flag_s(allOtherVars *peremn, flags *allflags) {
  if (peremn->c == '\n') {
    peremn->newStr = peremn->newStr + 1;
  }
  if (allflags->flags) {
    if (peremn->newStr == 1 && peremn->numc == 1) {
      peremn->newStr = 2;
      peremn->cntS = 1;
    }
    if (peremn->newStr < 3) {
      peremn->cntS = 1;
      if (peremn->c != '\n') peremn->newStr = 0;
    } else if (peremn->c != '\n') {
      peremn->newStr = 0;
      peremn->cntS = 1;
    }
  }
}

void flag_n(allOtherVars *peremn, flags *allflags) {
  if (allflags->flagn && !allflags->flagb) {
    if ((peremn->oldc == '\n' || peremn->numc == 1) && !allflags->flags) {
      printf("%6.d\t", peremn->num);
      peremn->num = peremn->num + 1;
    } else if (allflags->flags && (peremn->oldc == '\n' || peremn->numc == 1)) {
      if (peremn->cntS) {
        printf("%6.d\t", peremn->num);
        peremn->num = peremn->num + 1;
      }
    }
  }
}

void flag_b(allOtherVars *peremn, flags *allflags) {
  if (allflags->flagb) {
    if (!allflags->flags && (peremn->numc == 1 || peremn->oldc == '\n') &&
        peremn->c != '\n') {
      printf("%6.d\t", peremn->num);
      peremn->num = peremn->num + 1;
    }
    if (allflags->flags && (peremn->oldc == '\n' || peremn->numc == 1)) {
      if (peremn->c != '\n' && peremn->cntS) {
        printf("%6.d\t", peremn->num);
        peremn->num = peremn->num + 1;
      }
    }
  }
}

void flag_e(allOtherVars *peremn, flags *allflags) {
  if (allflags->flage) {
    if (!allflags->flags && peremn->c == '\n') {
      printf("$");
    } else if (peremn->cntS && peremn->c == '\n') {
      printf("$");
    }
  }
}

void flag_t(allOtherVars *peremn, flags *allflags) {
  if (allflags->flagt) {
    if (peremn->c == 9) peremn->cntT = 1;
  }
}

void flag_v(allOtherVars *peremn, flags *allflags) {
  if (allflags->flagv) {
    if (peremn->c >= 0 && peremn->c != 9 && peremn->c != 10 && peremn->c < 32) {
      printf("^%c", peremn->c + 64);
      peremn->cntV = 1;
    } else if (peremn->c == 127) {
      printf("^?");
      peremn->cntV = 1;
    }
  }
}

void output(allOtherVars *peremn, flags *allflags) {
  if (allflags->flags && peremn->cntS) {
    if (peremn->cntT) {
      printf("^I");
      peremn->cntS = 0;
      peremn->cntT = 0;
    } else if (peremn->cntV) {
      peremn->cntV = 0;
    } else {
      printf("%c", peremn->c);
      peremn->cntS = 0;
    }
  } else if (!allflags->flags) {
    if (peremn->cntT) {
      printf("^I");
      peremn->cntT = 0;
    } else if (peremn->cntV) {
      peremn->cntV = 0;
    } else {
      printf("%c", peremn->c);
    }
  }
}

void error() {
  perror("hehehe error");
  exit(1);
}