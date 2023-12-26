#ifndef S21_CAT_FUNCTION_H
#define S21_CAT_FUNCTION_H

#define PROGRAM_NAME "s21_cat"

typedef struct {
  size_t A;
  size_t b;
  size_t e;
  size_t E;
  size_t n;
  size_t s;
  size_t t;
  size_t T;
  size_t u;
  size_t v;
  size_t dash;
  size_t number_nonblank;
  size_t number;
  size_t squeeze_blank;
  size_t show_all;
  size_t show_ends;
  size_t show_tabs;
  size_t show_nonprinting;
  size_t version;
  size_t help;
} s_options_t;

void print_file(char* path);
void no_flags();
void parsing_args(int argc, char** argv, s_options_t* flags);
void print_line(const s_options_t flags, char* path);

#endif
