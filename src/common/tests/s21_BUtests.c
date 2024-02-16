#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char **argv) {
  DIR *dp = NULL;
  FILE *fp_gr = NULL;
  FILE *fp_sgr = NULL;
  char keys[] = "AbEensTtuv-";
  int number_of_keys = 0;
  int number_of_files = 0;

  srand(time(NULL));
  execvp("grep", argv);

  return 0;
}
