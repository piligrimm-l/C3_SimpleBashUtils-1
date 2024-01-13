#ifndef S21_GREP_H
#define S21_GREP_H

#define PROGRAM_NAME "s21_grep"

typedef struct {
  int a;
  int A;
  int b;
  int B;
  int c;
  int C;
  int d;
  int D;
  int e;
  int E;
  int f;
  int F;
  int G;
  int h;
  int H;
  int i;
  int I;
  int l;
  int L;
  int m;
  int n;
  int o;
  int P;
  int r;
  int R;
  int q;
  int s;
  int T;
  int U;
  int v;
  int V;
  int w;
  int x;
  int z;
  int Z;
  int binary_files = ;
  int color;
  int exclude = ;
  int exclude_dir = ;
  int exclude_from = ;
  int include = ;
  int group_separator = ;
  int no_group_separator;
  int label;
  int line_buffered;
  int no_ignore_case;
  int help;
} s_options_t;

void parsing_args(int argc, char** argv, s_options_t* flags);
void output(int argc, char** argv, s_options_t* flags, s_counters_t* counter);
void print_lines(s_options_t* flags, char* path, s_counters_t* counter);

#endif
