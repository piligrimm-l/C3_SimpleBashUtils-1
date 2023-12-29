#include "s21_cat_function.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void no_flags() {
  char ch;
  while ((ch = getchar()) != EOF) {
    putchar(ch);
  }
}

void print_file(char* path) {
  FILE* fp = fopen(path, "rt");
  DIR* dp = opendir(path);

  if (fp != NULL && dp == NULL) {
    int ch = fgetc(fp);
    while (ch != EOF) {
      putc(ch, stdout);
      ch = fgetc(fp);
    }
    fclose(fp);
  } else {
    if (dp != NULL) {
      printf("%s: %s: Is a directory", PROGRAM_NAME, path);
      closedir(dp);
      exit(EXIT_FAILURE);
    } else {
      printf("%s: %s: No such file or directory", PROGRAM_NAME, path);
      exit(EXIT_FAILURE);
    }
  }
}

void parsing_args(int argc, char** argv, s_options_t* flags) {
  for (int i = 1; i < argc; ++i) {
    if (strlen(argv[i]) > 0 && argv[i][0] == '-' && argv[i][1] != '-') {
      for (size_t j = 0; j < strlen(argv[i]); ++j) {
        switch (argv[i][j]) {
          case 'A':
            flags->A = 1;
            flags->v = 1;
            flags->E = 1;
            flags->T = 1;
            flags->show_all = 1;
            flags->show_nonprinting = 1;
            flags->show_ends = 1;
            flags->show_tabs = 1;
            break;
          case 'b':
            flags->n = 0;
            flags->number = 0;
            flags->b = 1;
            flags->number_nonblank = 1;
            break;
          case 'e':
            flags->e = 1;
            flags->v = 1;
            flags->E = 1;
            flags->show_ends = 1;
            flags->show_nonprinting = 1;
            break;
          case 'E':
            flags->E = 1;
            flags->show_ends = 1;
            break;
          case 'n':
            if (flags->b != 1) {
              flags->n = 1;
              flags->number = 1;
            }
            break;
          case 's':
            flags->s = 1;
            flags->squeeze_blank = 1;
            break;
          case 't':
            flags->t = 1;
            flags->T = 1;
            flags->v = 1;
            flags->show_tabs = 1;
            flags->show_nonprinting = 1;
            break;
          case 'T':
            flags->T = 1;
            flags->show_tabs = 1;
            break;
          case 'u':
            flags->u = 1;
            break;
          case 'v':
            flags->v = 1;
            flags->show_nonprinting = 1;
            break;
          case '-':
            if (strlen(argv[i]) == 1) {
              flags->dash = 1;
            }
            break;
          default:
            printf("%s: illegal option -- %c\n", PROGRAM_NAME, argv[i][j]);
            printf("usage: [-AbeEnstTuv] [file ...]");
            exit(EXIT_FAILURE);
            break;
        }
      }
    } else if (strlen(argv[i]) > 2 && argv[i][0] == '-' && argv[i][1] == '-') {
      if (!strcmp("--show-all", argv[i])) {
        flags->A = 1;
        flags->show_all = 1;
        flags->show_nonprinting = 1;
        flags->show_ends = 1;
        flags->show_tabs = 1;
        flags->v = 1;
        flags->E = 1;
        flags->T = 1;
      }
      if (!strcmp("--number-nonblank", argv[i])) {
        flags->n = 0;
        flags->number = 0;
        flags->b = 1;
        flags->number_nonblank = 1;
      }
      if (!strcmp("--show-ends", argv[i])) {
        flags->E = 1;
        flags->show_ends = 1;
      }
      if (!strcmp("--number", argv[i])) {
        flags->n = 1;
        flags->number = 1;
      }
      if (!strcmp("--squeeze-blank", argv[i])) {
        flags->s = 1;
        flags->squeeze_blank = 1;
      }
      if (!strcmp("--show-tabs", argv[i])) {
        flags->T = 1;
        flags->show_tabs = 1;
      }
      if (!strcmp("--show-nonprinting", argv[i])) {
        flags->v = 1;
        flags->show_nonprinting = 1;
      }
      if (!strcmp("--help", argv[i])) {
        flags->help = 1;
      }
      if (!strcmp("--version", argv[i])) {
        flags->version = 1;
      }
    }
  }
}

void output(int argc, char** argv, s_options_t* flags) {
  if (argc == 1 || (argc == 2 && argv[1][0] == '-' && strlen(argv[1]) == 1)) {
    no_flags();
  } else if (argc >= 2 && argv[1][0] != '-') {
    for (int i = 1; i < argc; ++i) {
      if (argv[i][0] == '-' && strlen(argv[i]) == 1 && flags->dash) {
        no_flags();
        flags->dash = 0;
      } else {
        print_file(argv[i]);
      }
    }
  } else {
    for (int i = 1; i != argc; ++i) {
      if (argv[i][0] != '-') {
        print_lines(flags, argv[i]);
      }
    }
  }
}

void print_lines(s_options_t* flags, char* path) {
  FILE* fp = fopen(path, "rt");
  DIR* dp = opendir(path);

  if (fp != NULL && dp == NULL) {
    int ch = fgetc(fp);
    while (ch != EOF) {
      while (ch != '\n' && ch != EOF) {
        if (ch == '\t' && (flags->t || flags->T || flags->show_tabs)) {
          putc('^', stdout);
          putc('I', stdout); 
          ch = fgetc(fp);
        }
        if (flags->v || flags->e || flags->t || flags->show_nonprinting || flags->A) {
          if (ch < 32 && ch != '\t') {
            ch = ch + 64;
            putc('^', stdout);
          } else if (ch == 127) {
            putc('^', stdout);
            putc('?', stdout);
          } else if (ch > 127 && ch < 160) {
            putc('M', stdout);
            putc('-', stdout);
            putc('^', stdout);
            ch = ch - 64; 
          }
        }
        putc(ch, stdout);
        ch = fgetc(fp);
      }
      if (ch != EOF) {
        putc(ch, stdout);
      }
      ch = fgetc(fp);
    }
    fclose(fp);
  } else {
    if (dp != NULL) {
      printf("%s: %s: Is a directory", PROGRAM_NAME, path);
      closedir(dp);
      exit(EXIT_FAILURE);
    } else {
      printf("%s: %s: No such file or directory", PROGRAM_NAME, path);
      exit(EXIT_FAILURE);
    }
  }
}
