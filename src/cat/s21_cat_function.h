#ifndef S21_CAT_FUNCTION_H
#define S21_CAT_FUNCTION_H

#define PROGRAM_NAME "s21_cat"

typedef struct {
  int A;
  int b;
  int e;
  int E;
  int n;
  int s;
  int t;
  int T;
  int u;
  int v;
  int dash;
  int number_nonblank;
  int number;
  int squeeze_blank;
  int show_all;
  int show_ends;
  int show_tabs;
  int show_nonprinting;
  int version;
  int help;
} s_options_t;

typedef struct {
  char prev;
  int lines;
  int empty_lines;
} s_counters_t;

void parsing_args(int argc, char** argv, s_options_t* flags);
void output(int argc, char** argv, s_options_t* flags, s_counters_t* counter);
void print_lines(s_options_t* flags, char* path, s_counters_t* counter);
void print_flags(s_options_t flags);

#endif
