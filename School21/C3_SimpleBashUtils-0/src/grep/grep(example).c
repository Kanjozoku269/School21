// Copyright 2022 school 21 hokkienw
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <getopt.h>
#include <string.h>

    int
    main(int argc, char *argv[]) {
  int ch; char short_options
  while ((ch = getopt_long(argc, argv, short_options, longopts, NULL)) != -1) {
    opt(ch, argv);
  }
  get_pattern(argv);
  readfile(argv, argc, optind);
}

void usage(void) {
  fprintf(stderr, "use: grep [-eivclnhsfo] template [file ...]\n");
  exit(1);
}

void opt(char c, char *argv[]) {
  switch (c) {
    case 'e':
      eflag = 1;
      get_pattern(argv);
      break;
    case 'i':
      iflag = 1;
      break;
    case 'v':
      vflag = 1;
      break;
    case 'c':
      cflag = 1;
      break;
    case 'l':
      lflag = 1;
      break;
    case 'n':
      nflag = 1;
      break;
    case 'h':
      hflag = 1;
      break;
    case 's':
      sflag = 1;
      break;
    case 'f':
      fflag = 1;
      get_pattern(argv);
      break;
    case 'o':
      oflag = 1;
      break;
    default:
      usage();
  }
}

void readfile(char *argv[], int argc, int optind) {
  FILE *file_name;
  char *path;
  int i = optind;
  while ((path = argv[i]) != NULL) {
    if (path != 0 || strcmp(path, "-") != 0) {
      if ((file_name = fopen(path, "r"))) {
        get_varriable(file_name, argc, path);
        fclose(file_name);
      } else {
        if (!sflag) {
          printf("grep: %s: No such file or directory\n", path);
        }
      }
    }
    i++;
  }
}

void get_pattern(char *argv[]) {
  char buffer[9000] = {0};
  if (!eflag && !fflag) {
    snprintf(pattern, sizeof(pattern), "%s", argv[optind]);
    optind++;
  }
  if (eflag && !fflag) {
    if (pattern[0] == 0) {
      snprintf(pattern, sizeof(pattern), "%s", optarg);
    } else {
      snprintf(buffer, sizeof(pattern), "|%s", optarg);
      strcat(pattern, buffer);
    }
  }
  if (fflag) {
    int i = 0;
    FILE *file_name_f;
    char *path;
    path = optarg;
    char tmp_line_f[810] = {0};
    if (path != NULL) {
      if ((file_name_f = fopen(path, "r"))) {
        while ((fgets(tmp_line_f, 800, file_name_f)) != NULL) {
          if (tmp_line_f[strlen(tmp_line_f) - 1] == 10) {
            tmp_line_f[strlen(tmp_line_f) - 1] = 0;
          }
          if (pattern[0] == 0) {
            snprintf(pattern, sizeof(pattern), "%s", tmp_line_f);
          } else {
            snprintf(buffer, sizeof(pattern), "|%s", tmp_line_f);
            strcat(pattern, buffer);
          }
          i++;
        }
      } else {
        if (!sflag) {
          printf("grep: %s: No such file or directory\n", path);
        }
      }
    }
  }
}

void get_varriable(FILE *file_name, int argc, char *path) {
  int rc;
  size_t len = 1000;
  int rez;
  char *tmp_line = NULL;
  int count_line = 0;
  int success = 0;
  int count_success = 0;
  regex_t regex;
  size_t nmatch = 4;
  regmatch_t pmatch[4];

  if (iflag && !eflag) {
    if ((rc = regcomp(&regex, pattern, REG_ICASE)) != 0) {
      printf("regcomp() failed, returning nonzero (%d)\n", rc);
      exit(1);
    }
  } else {
    if ((rc = regcomp(&regex, pattern, REG_EXTENDED)) != 0) {
      printf("regcomp() failed, returning nonzero (%d)\n", rc);
      exit(1);
    }
  }
  tmp_line = (char *)calloc(len, sizeof(char));
  while ((rez = getline(&tmp_line, &len, file_name)) != EOF) {
    if ((success = regexec(&regex, tmp_line, nmatch, pmatch, 0)) == 0) {
      count_success++;
    }
    if (tmp_line[strlen(tmp_line) - 1] == 10) {
      tmp_line[strlen(tmp_line) - 1] = 0;
    }
    if (!vflag && !cflag && !lflag && !oflag && success == 0) {
      if ((argc - optind) > 1 && !hflag) {
        printf("%s:", path);
      }
      if (nflag) {
        printf("%d:", count_line + 1);
      }
      printf("%s\n", tmp_line);
    }
    if (vflag && !cflag && !lflag && success != 0) {
      if ((argc - optind) > 1 && !hflag) {
        printf("%s:", path);
      }
      if (nflag) {
        printf("%d:", count_line + 1);
      }
      printf("%s\n", tmp_line);
    }
    if (!vflag && !cflag && !lflag && oflag && success == 0) {
      if ((argc - optind) > 1 && !hflag) {
        printf("%s:", path);
      }
      if (nflag) {
        21 : 54 printf("%d:", count_line + 1);
      }
      char *tmp_line_o = tmp_line;
      for (unsigned int m = 0; m < strlen(tmp_line_o); m++) {
        if (regexec(&regex, tmp_line_o, nmatch, pmatch, 0)) {
          break;
        }
        unsigned int offset = 0;
        for (size_t g = 0; g <= nmatch; g++) {
          if (pmatch[g].rm_so == -1) {
            break;
          }
          if (g == 0) {
            offset = pmatch[g].rm_eo;
          }
          char lineCopy[strlen(tmp_line_o) + 1];
          strcpy(lineCopy, tmp_line_o);
          lineCopy[pmatch[g].rm_eo] = 0;
          printf("%s\n", (lineCopy + pmatch[g].rm_so));
        }
        tmp_line_o += offset;
      }
    }
    count_line++;
  }
  if (!vflag && cflag && !lflag) {
    if ((argc - optind) > 1 && !hflag) {
      printf("%s:", path);
    }
    printf("%d\n", count_success);
  }
  if (vflag && cflag && !lflag) {
    if ((argc - optind) > 1 && !hflag) {
      printf("%s:", path);
    }
    printf("%d\n", (count_line - count_success));
  }
  if (!vflag && cflag && lflag) {
    if ((argc - optind) > 1 && !hflag) {
      printf("%s:", path);
    }
    if (count_success > 0) {
      printf("%d\n", 1);
    } else {
      printf("%d\n", 0);
    }
  }
  if (vflag && cflag && lflag) {
    if ((argc - optind) > 1 && !hflag) {
      printf("%s:", path);
    }
    if ((count_line - count_success) > 0) {
      printf("%d\n", 1);
    } else {
      printf("%d\n", 0);
    }
  }
  if (lflag && count_success > 0) {
    printf("%s\n", path);
  }
  if (vflag && lflag && count_success == 0) {
    printf("%s\n", path);
  }
  if (tmp_line) {
    free(tmp_line);
  }
  regfree(&regex);
}