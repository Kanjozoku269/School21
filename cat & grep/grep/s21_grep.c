#include "s21_grep.h"

int main(int argc, char *argv[]) {
  allflags flags = {0};
  allcounters counters = {0};

  switchs(argc, argv, &flags);
  funcReadPattern(argv, &flags);
  funcOpenFile(argv, &flags, argc, &counters);

  return 0;
}

void switchs(int argc, char *argv[], allflags *flags) {
  char c;
  while ((c = getopt_long(argc, argv, short_options, NULL, NULL)) != -1) {
    switch (c) {
      case 'e':  // паттерн
        flags->eflag = 1;
        funcReadPattern(argv, flags);
        break;
      case 'i':  // игнор регистра
        flags->iflag = 1;
        break;
      case 'v':  // инвертирует поиск соотв
        flags->vflag = 1;
        break;
      case 'c':  // только количество совпадений
        flags->cflag = 1;
        break;
      case 'l':  // только совпадающие файлы
        flags->lflag = 1;
        break;
      case 'n':  // выводит номер строки из файла
        flags->nflag = 1;
        break;
      case 'h':  // выводит строки без назв файлов
        flags->hflag = 1;
        break;
      case 's':  // без ошибок о несуществующих файлах
        flags->sflag = 1;
        break;
      case 'f':  // получает регулярки
        flags->fflag = 1;
        funcReadPattern(argv, flags);
        break;
      case 'o':  // выводит только совпадающиеся части
        flags->oflag = 1;
        break;
      case '?':
      default:
        errorflag();
    }
  }
}

void funcReadPattern(char *argv[], allflags *flags) {
  char string[SIZE] = {0};
  if (flags->eflag == 0 && flags->fflag == 0) {
    snprintf(patternFirst, sizeof(patternFirst), "%s", argv[optind]);
    optind++;
  }
  if (flags->eflag != 0 && flags->fflag == 0) {  // (e)
    if (patternFirst[0] == 0)
      snprintf(patternFirst, sizeof(patternFirst), "%s", optarg);
    else {
      snprintf(string, sizeof(patternFirst), "|%s", optarg);
      strcat(patternFirst, string);
    }
  }
  if (flags->fflag) {  // (f)
    funcF(string, flags);
  }
}

void funcOpenFile(char *argv[], allflags *flags, int argc,
                  allcounters *counters) {
  FILE *file;
  int fnm = optind;
  char *fileName;

  while ((fileName = argv[fnm]) != NULL) {
    if (strcmp(fileName, "-") != 0) {
      if ((file = fopen(argv[fnm], "r"))) {
        funcRegex(file, fileName, argc, counters, flags);
      } else {
        if (flags->sflag == 0) {
          perror("NO FILE");
          error();
        }
      }
    }
    fnm++;
  }
}

void funcRegex(FILE *file, char *fileName, int argc, allcounters *counters,
               allflags *flags) {
  int getLine = 0;
  int successCounter = 0;
  counters->counter = 0;
  counters->success = 0;
  funcRegexComp(flags);

  pattern = (char *)calloc(SIZE, sizeof(strLenght));
  if (pattern == NULL) error();
  while ((getLine = getline(&pattern, &strLenght, file)) != EOF) {
    counters->counter++;
    if ((counters->success = regexec(&regex, pattern, matchN, matchP, 0)) ==
        0) {
      successCounter++;
    }
    if (pattern[strlen(pattern) - 1] == '\n') {
      pattern[strlen(pattern) - 1] = '\0';
    }
    if (!flags->cflag) {  // c (c+n); (cv+n); (co+n)
      if (counters->success == 0 && !flags->vflag && !flags->lflag &&
          !flags->oflag) {
        funcWithoutH(argc, fileName, flags);
        if (flags->nflag) {
          printf("%d:", counters->counter);
        }
        printf("%s\n", pattern);
      }
      if (counters->success != 0 && flags->vflag && !flags->lflag) {
        funcWithoutH(argc, fileName, flags);
        if (flags->nflag) {
          printf("%d:", counters->counter);
        }
        printf("%s\n", pattern);
      }
      if (counters->success == 0 && !flags->vflag && !flags->lflag &&
          flags->oflag) {
        funcWithoutH(argc, fileName, flags);
        if (flags->nflag) {
          printf("%d:", counters->counter);
        }
        char *stringO = pattern;
        for (unsigned int l = 0; l < strlen(stringO); l++) {
          if (regexec(&regex, stringO, matchN, matchP, 0)) {
            break;
          }
          int end = 0;
          for (size_t size = 0; size <= matchN; size++) {
            if (matchP[size].rm_so == -1) {
              break;
            }
            if (size == 0) {
              end = matchP[size].rm_eo;
            }
            char buffer[strlen(stringO) + 1];
            strcpy(buffer, stringO);
            buffer[matchP[size].rm_eo] = 0;
            printf("%s\n", (buffer + matchP[size].rm_so));
          }
          stringO += end;
        }
      }
    }
  }
  if (flags->cflag) {  // (c+v); (c+vl); (c+l)
    if (!flags->vflag && !flags->lflag) {
      funcWithoutH(argc, fileName, flags);
      printf("%d\n", successCounter);
    }
    if (flags->vflag && !flags->lflag) {
      funcWithoutH(argc, fileName, flags);
      printf("%d\n", (counters->counter - successCounter));
    }
    if (flags->vflag && flags->lflag) {
      funcWithoutH(argc, fileName, flags);
      if ((counters->counter - successCounter) > 0) {
        printf("%d\n", 1);
      } else {
        printf("%d\n", 0);
      }
    }
    if (!flags->vflag && flags->lflag) {
      funcWithoutH(argc, fileName, flags);
      if (successCounter > 0) {
        printf("%d\n", 1);
      } else {
        printf("%d\n", 0);
      }
    }
  }

  if (flags->lflag != 0 && successCounter > 0) {  // (l); (v);
    printf("%s\n", fileName);
  }
  if (flags->vflag != 0 && flags->lflag && successCounter == 0) {
    printf("%s\n", fileName);
  }
  free(pattern);
  regfree(&regex);
}

void funcF(char *string, allflags *flags) {
  if (optarg != NULL) {
    FILE *fileF;
    if ((fileF = fopen(optarg, "r"))) {
      char patternF[SIZE2] = {0};
      while (fgets(patternF, 1024, fileF) != NULL) {
        if (patternF[strlen(patternF) - 1] == '\n') {
          patternF[strlen(patternF) - 1] = '\0';
        }
        if (patternFirst[0] == 0)
          snprintf(patternFirst, sizeof(patternFirst), "%s", patternF);
        else {
          snprintf(string, sizeof(patternFirst), "|%s", patternF);
          strcat(patternFirst, string);
        }
      }
    } else {
      if (flags->sflag == 0) {
        error();
      }
      fclose(fileF);
    }
  }
}

void funcRegexComp(allflags *flags) {
  int statusRegComp;
  if (flags->iflag) {
    if ((statusRegComp = regcomp(&regex, patternFirst, REG_ICASE)) != 0) {
      printf("failed - %d", statusRegComp);
      error();
    }
  } else {
    if ((statusRegComp = regcomp(&regex, patternFirst, REG_EXTENDED)) != 0) {
      printf("failed - %d", statusRegComp);
      error();
    }
  }
}

void funcWithoutH(int argc, char *fileName, allflags *flags) {
  if ((argc - optind) > 1 && !flags->hflag) {
    printf("%s:", fileName);
  }
}

void errorflag() {
  perror("use: grep [-eivclnhsfo] template [file ...]");
  exit(1);
}
void error() {
  perror("hehehe error elki palki");
  exit(1);
}
