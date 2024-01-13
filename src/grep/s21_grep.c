#include "s21_grep.h"

int main(int argc, char** argv) {
  s_options_t flags = {0};
  // s_counters_t counter = {0};

  parsing_args(argc, argv, &flags);
  output(argc, argv, &flags);

  return 0;
}
