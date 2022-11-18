#ifndef SRC_CAT_S21_CAT_H
#define SRC_CAT_S21_CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

static struct option long_options[] = {
    {"number-nonblank", 0, 0, 'b'},
    {"number", 0, 0, 'n'},
    {"squeeze-blank)", 0, 0, 's'},
};

FILE *file;

typedef struct {
  int num;
  int numc;
  int countSym;
  int countS;
  int newStr;
  int countT;
  int countV;
  int cntS;
  int cntT;
  int cntV;
  char c;
  char oldc;
} allOtherVars;

typedef struct {
  int flagb;
  int flagn;
  int flage;
  int flagv;
  int flags;
  int flagt;
} flags;

void switchs(char flag, flags *allflags);
void open_file(char *argv[]);
void flag_s(allOtherVars *peremn, flags *allflags);
void flag_n(allOtherVars *peremn, flags *allflags);
void flag_b(allOtherVars *peremn, flags *allflags);
void flag_e(allOtherVars *peremn, flags *allflags);
void flag_t(allOtherVars *peremn, flags *allflags);
void flag_v(allOtherVars *peremn, flags *allflags);
void output(allOtherVars *peremn, flags *allflags);
void error();

#endif  // SRC_CAT_S21_CAT_H_