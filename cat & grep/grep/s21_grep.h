#ifndef S21_GREP_H_
#define S21_GREP_H_

#define SIZE 2056
#define SIZE2 2055
#define mp 2
#define sizeStr 200

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *short_options = "e:ivclnhsf:o?+";

typedef struct flags {
  int eflag;
  int iflag;
  int vflag;
  int cflag;
  int lflag;
  int nflag;
  int hflag;
  int sflag;
  int fflag;
  int oflag;
} allflags;

regex_t regex;
regmatch_t matchP[mp];
size_t matchN = mp;
size_t strLenght = sizeStr;
char patternFirst[SIZE];
char *pattern = {0};

typedef struct counters {
  int counter;
  int success;
} allcounters;

void error();
void errorflag();
void switchs(int argc, char *argv[], allflags *flags);
void funcOpenFile(char *argv[], allflags *flags, int argc,
                  allcounters *counters);
void funcReadPattern(char *argv[], allflags *flags);
void funcRegex(FILE *file, char *fileName, int argc, allcounters *counters,
               allflags *flags);
void funcRegexComp(allflags *flags);
void funcF(char *counterstring, allflags *flags);
void funcWithoutH(int argc, char *fileName, allflags *flags);

#endif  // S21_GREP_H_
