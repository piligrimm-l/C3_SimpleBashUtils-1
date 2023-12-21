#include <dirent.h>
#include <stdio.h>
#include <string.h>

void no_flags() {
  char ch;
  while ((ch = getchar()) != EOF) continue;
}

void print_file(char* path) {
  FILE* fp = fopen(path, "rt");
  DIR* dp = opendir(path);

  if (fp != NULL && dp == NULL) {
    int ch = fgetc(fp);
    while (ch != EOF) {
      putc(ch, stdout);
      ch = fgetc(fp);
    }
    fclose(fp);
  } else {
    if (dp != NULL) {
      printf("s21_cat.out: %s: Is a directory", path);
      closedir(dp);
    } else {
      printf("s21_cat.out: %s: No such file or directory", path);
    }
  }
}

void parsing_args(char* flag) { if (strlen(flag) > 2) }
