#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_grep.h"

void parsing_args(int argc, char** argv, s_options_t* flags) {
  for (int i = 1; i < argc; ++i) {
    if (strlen(argv[i]) > 0 && argv[i][0] == '-' && argv[i][1] != '-') {
      for (size_t j = 0; j < strlen(argv[i]); ++j) {
        switch (argv[i][j]) {
          case 'a':
            flags->a = 1;
            break;
          case 'A':
            flags->A = 1;
            break;
          case 'b':
            flags->b = 1;
            break;
          case 'B':
            flags->B = 1;
            break;
          case 'c':
            flags->c = 1;
            break;
          case 'C':
            flags->C = 1;
            break;
          case 'd':
            flags->d = 1;
            break;
          case 'D':
            flags->D = 1;
            break;
          case 'e':
            flags->e = 1;
            break;
          case 'E':
            flags->E = 1;
            break;
          case 'f':
            flags->f = 1;
            break;
          case 'F':
            flags->F = 1;
            break;
          case 'G':
            flags->G = 1;
            break;
          case 'h':
            flags->h = 1;
            break;
          case 'H':
            flags->H = 1;
            break;
          case 'i':
          case 'y':
            flags->i = 1;
            break;
          case 'I':
            flags->I = 1;
            break;
          case 'l':
            flags->l = 1;
            break;
          case 'L':
            flags->L = 1;
            break;
          case 'm':
            flags->m = 1;
            break;
          case 'n':
            flags->n = 1;
            break;
          case 'o':
            flags->o = 1;
            break;
          case 'P':
            flags->P = 1;
            break;
          case 'r':
            flags->r = 1;
            break;
          case 'R':
            flags->R = 1;
            break;
          case 'q':
            flags->q = 1;
            break;
          case 's':
            flags->s = 1;
            break;
          case 'T':
            flags->T = 1;
            break;
          case 'U':
            flags->U = 1;
            break;
          case 'v':
            flags->v = 1;
            break;
          case 'V':
            flags->V;
            break;
          case 'w':
            flags->w = 1;
            break;
          case 'x':
            flags->x;
            break;
          case 'z':
            flags->z;
            break;
          case 'Z':
            flags->Z;
            break;
          default:
            printf("%s: illegal option -- %c\n", PROGRAM_NAME, argv[i][j]);
            printf("usage: [-AbeEnstTuv] [file ...]");
            exit(EXIT_FAILURE);
            break;
        }
      }
    } else if (strlen(argv[i]) > 2 && argv[i][0] == '-' && argv[i][1] == '-') {
      if (!strcmp("--text", argv[i])) {
        flags->a = 1;
      } else if (!strcmp("--after-context=", argv[i])) {
        flags->A = 1;
      } else if (!strcmp("--byte-offset", argv[i])) {
        flags->b = 1;
      } else if (!strcmp("--before-context=", argv[i])) {
        flags->B = 1;
      } else if (!strcmp("--count", argv[i])) {
        flags->c = 1;
      } else if (!strcmp("--context=", argv[i])) {
        flags->C = 1;
      } else if (!strcmp("--directories=", argv[i])) {
        flags->d = 1;
      } else if (!strcmp("--devices=", argv[i])) {
        flags->D = 1;
      } else if (!strcmp("--regexp=", argv[i])) {
        flags->e = 1;
      } else if (!strcmp("--extended-regexp", argv[i])) {
        flags->E = 1;
      } else if (!strcmp("--file=", argv[i])) {
        flags->f = 1;
      } else if (!strcmp("--fiixed-strings", argv[i])) {
        flags->F = 1;
      } else if (!strcmp("--basic-regexp", argv[i])) {
        flags->G = 1;
      } else if (!strcmp("--no-filename", argv[i])) {
        flags->h = 1;
      } else if (!strcmp("--with-filename", argv[i])) {
        flags->H = 1;
      } else if (!strcmp("--ignoge-case", argv[i])) {
        flags->i = 1;
      } else if (!strcmp("--files-with-matches", argv[i])) {
        flags->l = 1;
      } else if (!strcmp("--files-without-match", argv[i])) {
        flags->L = 1;
      } else if (!strcmp("--max-count=", argv[i])) {
        flags->m = 1;
      } else if (!strcmp("--line-number", argv[i])) {
        flags->n = 1;
      } else if (!strcmp("--only-matching", argv[i])) {
        flags->o = 1;
      } else if (!strcmp("--perl-regexp", argv[i])) {
        flags->P = 1;
      } else if (!strcmp("--quiet", argv[i]) || !strcmp("--silent", argv[i])) {
        flags->q = 1;
      } else if (!strcmp("--no-messages", argv[i])) {
        flags->s = 1;
      } else if (!strcmp("--invert-match", argv[i])) {
        flags->v = 1;
      } else if (!strcmp("--word-regexp", argv[i])) {
        flags->w = 1;
      } else if (!strcmp("--line-regexp", argv[i])) {
        flags->x = 1;
      } else if (!strcmp("--color", argv[i]) || !strcmp("--colour", argv[i])) {
        flags->color = 1;
      } else if (!strcmp("--no-ignore-case", argv[i])) {
        flags->no_ignore_case = 1;
      } else if (!strcmp("--help", argv[i])) {
        flags->help = 1;
      } else if (!strcmp("--version", argv[i])) {
        flags->V = 1;
      } else {
        printf("%s: illegal option -- %s\n", PROGRAM_NAME, argv[i]);
        printf("usage: [-AbeEnstTuv] [file ...]");
        exit(EXIT_FAILURE);
      }
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
#if __linux__
          if (!(ch == 94 && counter->prev == 0)) {
            printf("%6d\t", ++counter->lines);
          }
#else

          printf("%6d\t", ++counter->lines);
#endif
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
        if (!((ch == 255 || ch == 127) &&
              (flags->v || flags->e || flags->t || flags->A))) {
          putc(ch, stdout);
        }
        counter->prev = ch;
        ch = fgetc(fp);
        ++character_counter;
      }
      if (ch == '\n') {
        if (counter->prev != '\n') {
          counter->empty_lines = 0;
        }
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
