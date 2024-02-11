#include "s21_grep.h"

int main(int argc, char** argv) {
  s_options_t flags = {0};
  s_list_t* patterns = NULL;
  s_list_t* fpatterns = NULL;
  s_list_t* paths = NULL;

  patterns = create_list();
  fpatterns = create_list();
  paths = create_list();

  parsing_args(argc, argv, &flags, patterns, fpatterns, paths);
  no_file_name(paths, patterns);
  write_fpatterns(fpatterns, patterns);

  output(&flags, patterns, paths);

  delete_list(patterns);
  delete_list(fpatterns);
  delete_list(paths);

  return 0;
}
