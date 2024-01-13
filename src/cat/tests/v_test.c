#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  FILE* fp = fopen(argv[1], "w");
  if (fp != NULL) {
    for (size_t i = 0; i != 256; ++i) {
      putc(i, fp);
    }
    fclose(fp);
  } else {
    printf("No such file %s", argv[1]);
    exit(EXIT_FAILURE);
  }
  return 0;
}
