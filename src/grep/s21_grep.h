#ifndef S21_GREP_H
#define S21_GREP_H

#include <dirent.h>
#include <errno.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/s21_list_functions.h"

#define PROGRAM_NAME "s21_grep"
#define BUFFER_SIZE 512

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
  int binary_files;
  int color;
  int exclude;
  int exclude_dir;
  int exclude_from;
  int group_separator;
  int help;
  int include;
  int label;
  int line_buffered;
  int no_group_separator;
  int no_ignore_case;
} s_options_t;

typedef struct {
  int pn_color;
  int fn_color;
  int colon_color;
  int number_line_color;
} s_chcolor_t;

void parsing_args(int argc, char** argv, s_options_t* flags, s_list_t* patterns,
                  s_list_t* fpatterns, s_list_t* paths);
void scan_pattern(s_list_t* patterns, s_list_t* fpatterns, s_list_t* paths,
                  int argc, char** argv, int* i, size_t* j);
void scan_args_1_2(char** argv, s_options_t* flags, s_list_t* patterns,
                   s_list_t* paths);
int scan_color_flags(char** argv, int i);
void write_fpatterns(s_list_t* fpatterns, s_list_t* patterns);
void no_file_name(s_list_t* paths, const s_list_t* patterns);
void search_patterns(FILE* fp, const s_list_t* patterns, const s_list_t* paths,
                     char* file_name, const s_options_t* flags);
char* read_line(FILE* fp);
void output(const s_options_t* flags, const s_list_t* patterns,
            const s_list_t* paths);
void print_line(const char* str, const size_t* app, size_t index,
                const s_chcolor_t* colors, const s_options_t* flags);
size_t* search_regex(char* str, const s_list_t* patterns, size_t* index,
                     const s_options_t* flags);
void print_regerror(int errnum, regex_t regex);
void print_error(const char* program_name, const char* file_name,
                 const char* message);
void* ptr_realloc(void* data, size_t* data_size, size_t type_size);
void clean_pointer(void* ptr);
void n_option(const s_options_t* flags, const int* count_lines,
              const s_chcolor_t* colors);
void c_option(const s_options_t* flags, const s_list_t* paths, char* file_name,
              const int* count_matches, const s_chcolor_t* colors);
void e_option(const s_options_t* flags, const char* str, const s_list_t* paths,
              const s_chcolor_t* colors, char* file_name, size_t index,
              int count_lines, const size_t* app);
void v_option(const s_options_t* flags, const char* const str,
              const s_list_t* paths, const s_chcolor_t* coloks, char* file_name,
              int count_lines);
void o_option(const char* str, size_t* app, size_t index, int count_lines,
              const s_chcolor_t* colors, const s_options_t* flags,
              const s_list_t* paths, char* file_name);
void print_pattern(const char* str, const size_t* app, size_t i,
                   const s_options_t* flags, const s_chcolor_t* colors);
void l_option(const s_options_t* flags, const s_chcolor_t* colors,
              char* file_names);
void print_lists(s_list_t* patterns, s_list_t* fpatterns, s_list_t* paths);

#endif
