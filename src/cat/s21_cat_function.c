#include "s21_cat_function.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
              ++flags->dash;
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
      } else if (!strcmp("--number-nonblank", argv[i])) {
        flags->n = 0;
        flags->number = 0;
        flags->b = 1;
        flags->number_nonblank = 1;
      } else if (!strcmp("--show-ends", argv[i])) {
        flags->E = 1;
        flags->show_ends = 1;
      } else if (!strcmp("--number", argv[i])) {
        flags->n = 1;
        flags->number = 1;
      } else if (!strcmp("--squeeze-blank", argv[i])) {
        flags->s = 1;
        flags->squeeze_blank = 1;
      } else if (!strcmp("--show-tabs", argv[i])) {
        flags->T = 1;
        flags->show_tabs = 1;
      } else if (!strcmp("--show-nonprinting", argv[i])) {
        flags->v = 1;
        flags->show_nonprinting = 1;
      } else if (!strcmp("--help", argv[i])) {
        flags->help = 1;
      } else if (!strcmp("--version", argv[i])) {
        flags->version = 1;
      } else {
        printf("%s: illegal option -- %s\n", PROGRAM_NAME, argv[i]);
        printf("usage: [-AbeEnstTuv] [file ...]");
        exit(EXIT_FAILURE);
      }
    } else {
#ifdef __APPLE__

      if (argv[i][0] != '-') {
        break;
      }

#endif
    }
  }
}

void output(int argc, char** argv, s_options_t* flags, s_counters_t* counter) {
  if (argc == 1 || !strcmp(argv[1], "--")) {
    print_lines(flags, "-", counter);
  } else if (flags->version) {
    printf("%s - program version 0.01 from 01/18/2024", PROGRAM_NAME);
    exit(EXIT_SUCCESS);
  } else if (flags->help) {
    s_options_t flags_0 = {0};
    print_lines(&flags_0, "tests/help_s21_cat.txt", counter);
    exit(EXIT_SUCCESS);
  } else if (argc > 1) {
    for (int i = 1; i != argc; ++i) {
      if (argv[i][0] != '-' || !strcmp(argv[i], "-")) {
        print_lines(flags, argv[i], counter);
        if (!strcmp(argv[i], "-")) {
          --flags->dash;
        }
      }
    }
  }
}

void print_lines(s_options_t* flags, char* path, s_counters_t* counter) {
  FILE* fp = NULL;
  if (!strcmp(path, "-")) {
    fp = freopen("/dev/tty", "rt", stdin);
  } else {
    fp = fopen(path, "rt");
  }
  DIR* dp = opendir(path);
  int character_counter = 0;
  counter->prev = '\0';

#ifdef __APPLE__

  counter->lines = 0;
  counter->empty_lines = 0;

#endif

  if (fp != NULL && dp == NULL) {
    int ch = fgetc(fp);
    ++character_counter;
    if (ch == '\n') {
      counter->empty_lines = 1;
    }
    while (ch != EOF) {
      while (ch != '\n' && ch != EOF) {
        if ((flags->b || flags->number_nonblank || flags->n || flags->number) &&
            character_counter == 1) {
          if (!(ch == 94 && counter->prev == 0)) {
            printf("%6d\t", ++counter->lines);
          }
        }
        if (ch == '\t' && (flags->t || flags->T || flags->show_tabs ||
                           flags->A || flags->show_all)) {
          putc('^', stdout);
          putc('I', stdout);
          counter->prev = ch;
          ch = fgetc(fp);
          ++character_counter;
          continue;
        }
        if (flags->v || flags->e || flags->t || flags->show_nonprinting ||
            flags->A || flags->show_all) {
          if (ch < 32 && ch != '\t') {
            ch = ch + 64;
            putc('^', stdout);
          } else if (ch == 127 || ch == 255) {
            if (ch == 255) {
              putc('M', stdout);
              putc('-', stdout);
            }
            putc('^', stdout);
            putc('?', stdout);
          } else if (ch > 127 && ch < 160) {
            putc('M', stdout);
            putc('-', stdout);
            putc('^', stdout);
            ch = ch - 64;
          }
#ifdef __linux__

          else if (ch > 159 && ch < 255) {
            putc('M', stdout);
            putc('-', stdout);
            ch -= 128;
          }

#endif
        }
        if (ch != 255) {
          if (ch == 127) printf("%c", 127);
          putc(ch, stdout);
        }
        counter->prev = ch;
        ch = fgetc(fp);
        ++character_counter;
      }
      if (ch == '\n') {
        if ((flags->n || flags->number) && character_counter == 1 &&
            (!counter->empty_lines || counter->prev != '\n')) {
          printf("%6d\t", ++counter->lines);
        }
        if ((flags->s || flags->squeeze_blank) && counter->prev == '\n') {
          if (!counter->empty_lines) {
            if (flags->e || flags->E || flags->show_ends || flags->A ||
                flags->show_all) {
              putc('$', stdout);
            }
            putc(ch, stdout);
            ++counter->empty_lines;
          }
          counter->prev = ch;
          ch = fgetc(fp);
          character_counter = 0;
          if (ch != '\n') {
            counter->empty_lines = 0;
            ++character_counter;
          }
          continue;
        } else if (ch != EOF) {
          if (flags->e || flags->E || flags->show_ends || flags->A ||
              flags->show_all) {
            putc('$', stdout);
          }
          putc(ch, stdout);
          character_counter = 0;
        }
      }
      counter->prev = ch;
      ch = fgetc(fp);
      ++character_counter;
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

/*void print_flags(s_options_t flags) {
  printf("flags.A = %d\n", flags.A);
  printf("flags.b = %d\n", flags.b);
  printf("flags.e = %d\n", flags.e);
  printf("flags.E = %d\n", flags.E);
  printf("flags.n = %d\n", flags.n);
  printf("flags.s = %d\n", flags.s);
  printf("flags.t = %d\n", flags.t);
  printf("flags.T = %d\n", flags.T);
  printf("flags.u = %d\n", flags.u);
  printf("flags.v = %d\n", flags.v);
  printf("flags.dash = %d\n", flags.dash);
  printf("flags.show_all = %d\n", flags.show_all);
  printf("flags.number_nonblank = %d\n", flags.number_nonblank);
  printf("flags.show_ends = %d\n", flags.show_ends);
  printf("flags.number = %d\n", flags.number);
  printf("flags.squeeze_blank = %d\n", flags.squeeze_blank);
  printf("flags.show_tabs = %d\n", flags.show_tabs);
  printf("flags.show_nonprinting = %d\n", flags.show_nonprinting);
  printf("flags.help = %d\n", flags.help);
  printf("flags.version = %d\n", flags.version);
}*/
