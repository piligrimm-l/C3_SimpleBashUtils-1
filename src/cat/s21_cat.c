#include <stdio.h>

#include "s21_cat_function.h"

int main(int argc, char** argv) {
  s_options_t flags = {0};

  parsing_args(argc, argv, &flags);
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

  for (int i = 0; i < argc; ++i) {
    if (argv[i][0] != '-') {
      print_line(flags, argv[i]);
    }
  }

  /*if (argc == 1) {
    no_flags();
  } else if (argc == 2) {
    print_file(argv[1]);
  } else if (argv[1][0] != '-') {
    for (size_t i = 1; i < argc; ++i) {
      print_file(argv[i]);
    }
  } else {
  }*/
  return 0;
}
