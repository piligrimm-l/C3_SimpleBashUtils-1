#include "s21_cat_function.h"

int main(int argc, char** argv) {
  s_options_t flags = {0};

  parsing_args(argc, argv, &flags);
  //print_flags(flags);
  output(argc, argv, &flags);

  return 0;
}
