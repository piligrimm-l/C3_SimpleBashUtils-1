#include "s21_grep.h"

int main(int argc, char** argv) {
  printf("%d", argc);
  execvp("grep", argv);

  return 0;
}
