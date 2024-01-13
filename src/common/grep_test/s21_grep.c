#include <stdio.h>
#include <unistd.h>

#define SIZE 100

int main(int argc, char** argv) {
  printf("%d", argc);
  execvp("grep", argv);

  return 0;
}
