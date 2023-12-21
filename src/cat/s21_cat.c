#include <stdio.h>

#include "s21_cat_function.h"

int main(int argc, char** argv) {
  if (argc == 1) {
    no_flags();
  } else if (argc == 2) {
    print_file(argv[1]);
  } else if (argv[1][0] != '-') {
    for (size_t i = 1; i < argc; ++i) {
      print_file(argv[i]);
    }
  } else {
    // switch (flag) {
    //    case 'e':

    //}
  }
  return 0;
}
