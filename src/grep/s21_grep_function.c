#include "s21_grep.h"

void parsing_args(int argc, char** argv, s_options_t* flags, s_list_t* patterns,
                  s_list_t* fpatterns, s_list_t* paths) {
  errno = 0;
  for (int i = 1; i != argc; ++i) {
    if (strlen(argv[i]) > 1 && argv[i][0] == '-' && argv[i][1] != '-') {
      for (size_t j = 1; j != strlen(argv[i]); ++j) {
        switch (argv[i][j]) {
          case 'a':
            flags->a = 1;
            break;
          case 'A':
            flags->A = 1;
            break;
          case 'b':
            flags->b = 1;
            break;
          case 'B':
            flags->B = 1;
            break;
          case 'c':
            flags->c = 1;
            break;
          case 'C':
            flags->C = 1;
            break;
          case 'd':
            flags->d = 1;
            break;
          case 'D':
            flags->D = 1;
            break;
          case 'e':
            ++flags->e;
            scan_pattern(patterns, fpatterns, paths, argc, argv, &i, &j);
            break;
          case 'E':
            flags->E = 1;
            break;
          case 'f':
            ++flags->f;
            scan_pattern(patterns, fpatterns, paths, argc, argv, &i, &j);
            break;
          case 'F':
            flags->F = 1;
            break;
          case 'G':
            flags->G = 1;
            break;
          case 'h':
            if (flags->H) {
              flags->H = 0;
            }
            flags->h = 1;
            break;
          case 'H':
            if (flags->h) {
              flags->h = 0;
            }
            flags->H = 1;
            break;
          case 'i':
          case 'y':
            flags->i = 1;
            break;
          case 'I':
            flags->I = 1;
            break;
          case 'l':
            flags->l = 1;
            break;
          case 'L':
            flags->L = 1;
            break;
          case 'm':
            flags->m = 1;
            break;
          case 'n':
            flags->n = 1;
            break;
          case 'o':
            flags->o = 1;
            break;
          case 'P':
            flags->P = 1;
            break;
          case 'r':
            flags->r = 1;
            break;
          case 'R':
            flags->R = 1;
            break;
          case 'q':
            flags->q = 1;
            break;
          case 's':
            flags->s = 1;
            break;
          case 'T':
            flags->T = 1;
            break;
          case 'U':
            flags->U = 1;
            break;
          case 'v':
            flags->v = 1;
            break;
          case 'V':
            flags->V = 1;
            break;
          case 'w':
            flags->w = 1;
            break;
          case 'x':
            flags->x = 1;
            break;
          case 'z':
            flags->z = 1;
            break;
          case 'Z':
            flags->Z = 1;
            break;
          default:
            printf("%s: illegal option -- \"%c\"\n", PROGRAM_NAME, argv[i][j]);
            exit(EXIT_FAILURE);
        }
      }
    } else if (strlen(argv[i]) > 2 && argv[i][0] == '-' && argv[i][1] == '-') {
      if (!strcmp("--text", argv[i])) {
        flags->a = 1;
      } else if (!strcmp("--after-context=", argv[i])) {
        flags->A = 1;
      } else if (!strcmp("--byte-offset", argv[i])) {
        flags->b = 1;
      } else if (!strcmp("--before-context=", argv[i])) {
        flags->B = 1;
      } else if (!strcmp("--count", argv[i])) {
        flags->c = 1;
      } else if (!strcmp("--context=", argv[i])) {
        flags->C = 1;
      } else if (!strcmp("--directories=", argv[i])) {
        flags->d = 1;
      } else if (!strcmp("--devices=", argv[i])) {
        flags->D = 1;
      } else if (strstr(argv[i], "--regexp=")) {
        ++flags->e;
        insert_list_item(patterns, 1, &argv[i][9]);
      } else if (!strcmp("--extended-regexp", argv[i])) {
        flags->E = 1;
      } else if (strstr(argv[i], "--file=")) {
        flags->f = 1;
        insert_list_item(fpatterns, 1, &argv[i][7]);
      } else if (!strcmp("--fiixed-strings", argv[i])) {
        flags->F = 1;
      } else if (!strcmp("--basic-regexp", argv[i])) {
        flags->G = 1;
      } else if (!strcmp("--no-filename", argv[i])) {
        flags->h = 1;
      } else if (!strcmp("--with-filename", argv[i])) {
        flags->H = 1;
      } else if (!strcmp("--ignore-case", argv[i])) {
        flags->i = 1;
      } else if (!strcmp("--files-with-matches", argv[i])) {
        flags->l = 1;
      } else if (!strcmp("--files-without-match", argv[i])) {
        flags->L = 1;
      } else if (!strcmp("--max-count=", argv[i])) {
        flags->m = 1;
      } else if (!strcmp("--line-number", argv[i])) {
        flags->n = 1;
      } else if (!strcmp("--only-matching", argv[i])) {
        flags->o = 1;
      } else if (!strcmp("--perl-regexp", argv[i])) {
        flags->P = 1;
      } else if (!strcmp("--recursive", argv[i])) {
        flags->r = 1;
      } else if (!strcmp("--dereference-recursive", argv[i])) {
        flags->R = 1;
      } else if (!strcmp("--quiet", argv[i]) || !strcmp("--silent", argv[i])) {
        flags->q = 1;
      } else if (!strcmp("--no-messages", argv[i])) {
        flags->s = 1;
      } else if (!strcmp("--initial-tab", argv[i])) {
        flags->T = 1;
      } else if (!strcmp("--binary", argv[i])) {
        flags->U = 1;
      } else if (!strcmp("--invert-match", argv[i])) {
        flags->v = 1;
      } else if (!strcmp("--version", argv[i])) {
        flags->V = 1;
      } else if (!strcmp("--word-regexp", argv[i])) {
        flags->w = 1;
      } else if (!strcmp("--line-regexp", argv[i])) {
        flags->x = 1;
      } else if (!strcmp("--null-data", argv[i])) {
        flags->z = 1;
      } else if (!strcmp("--null", argv[i])) {
        flags->Z = 1;
      } else if (!strcmp("--binary-files=", argv[i])) {
        flags->binary_files = 1;
      } else if (scan_color_flags(argv, i)) {
        if (scan_color_flags(argv, i) == 1) {
          flags->color = 1;
        } else {
          flags->color = 0;
        }
      } else if (!strcmp("--exclude=", argv[i])) {
        flags->exclude = 1;
      } else if (!strcmp("--exclude-dir=", argv[i])) {
        flags->exclude_dir = 1;
      } else if (!strcmp("--exclude-from=", argv[i])) {
        flags->exclude_from = 1;
      } else if (!strcmp("--group-separator=", argv[i])) {
        flags->group_separator = 1;
      } else if (!strcmp("--help", argv[i])) {
        flags->help = 1;
      } else if (!strcmp("--include=", argv[i])) {
        flags->include = 1;
      } else if (!strcmp("--label=", argv[i])) {
        flags->label = 1;
      } else if (!strcmp("--line-buffered", argv[i])) {
        flags->line_buffered = 1;
      } else if (!strcmp("--no-group-separator", argv[i])) {
        flags->no_group_separator = 1;
      } else if (!strcmp("--no-ignore-case", argv[i])) {
        flags->no_ignore_case = 1;
      } else {
        printf("%s: illegal option -- %s\n", PROGRAM_NAME, argv[i]);
        exit(EXIT_FAILURE);
      }
    } else {
      if (i != 1 && i != 2) {
        insert_list_item(paths, 1, argv[i]);
      }
    }
  }
  scan_args_1_2(argv, flags, patterns, paths);
}

void scan_pattern(s_list_t* patterns, s_list_t* fpatterns, s_list_t* paths,
                  int argc, char** argv, int* i, size_t* j) {
  if (*j == (strlen(argv[*i]) - 1)) {
    if (argv[*i][*j] == 'e') {
      insert_list_item(patterns, 1, argv[++(*i)]);
      if (*i + 1 != argc &&
          (argv[*i + 1][0] != '-' || !strcmp(argv[*i + 1], "-"))) {
        insert_list_item(paths, -1, argv[++(*i)]);
      }
    }
    if (argv[*i][*j] == 'f') {
      insert_list_item(fpatterns, 1, argv[++(*i)]);
    }
    *j = strlen(argv[*i]) - 1;
  } else if (*j < strlen(argv[*i]) - 1) {
    if (argv[*i][*j] == 'e') {
      insert_list_item(patterns, 1, &argv[*i][++(*j)]);
      if (*i + 1 != argc &&
          (argv[*i + 1][0] != '-' || !strcmp(argv[*i + 1], "-"))) {
        insert_list_item(paths, -1, argv[++(*i)]);
      }
    }
    if (argv[*i][*j] == 'f') {
      insert_list_item(fpatterns, 1, &argv[*i][++(*j)]);
    }
    *j = strlen(argv[*i]) - 1;
  }
}

void scan_args_1_2(char** argv, s_options_t* flags, s_list_t* patterns,
                   s_list_t* paths) {
  if (flags->e) {
    if (argv[1][0] != '-' || !strcmp(argv[1], "-")) {
      insert_list_item(paths, -1, argv[1]);
      if (argv[2][0] != '-' || !strcmp(argv[2], "-")) {
        insert_list_item(paths, -1, argv[2]);
      }
    } else {
      if (!strchr(argv[1], 'e')) {
        if (argv[2][0] != '-' || !strcmp(argv[2], "-")) {
          insert_list_item(paths, -1, argv[2]);
        }
      }
    }
  } else {
    if (argv[1][0] != '-' || !strcmp(argv[1], "-")) {
      ++flags->e;
      insert_list_item(patterns, -1, argv[1]);
      if (argv[2][0] != '-' || !strcmp(argv[2], "-")) {
        insert_list_item(paths, -1, argv[2]);
      }
    } else {
      if (argv[2][0] != '-' || !strcmp(argv[2], "-")) {
        ++flags->e;
        insert_list_item(patterns, -1, argv[2]);
      }
    }
  }
}

void write_fpatterns(s_list_t* fpatterns, s_list_t* patterns) {
  FILE* fp = NULL;
  DIR* dp = NULL;
  char* pattern = NULL;
  errno = 0;
  s_list_item_t* current_fpatterns = fpatterns->head;
  while (current_fpatterns) {
    if (!strcmp(current_fpatterns->data, "-")) {
      fp = freopen("/dev/tty", "r", stdin);
    } else {
      fp = fopen(current_fpatterns->data, "r");
      dp = opendir(current_fpatterns->data);
    }
    if (fp) {
      pattern = read_line(fp);
      while (pattern[0] != '\0') {
        *strchr(pattern, '\n') = '\0';
        insert_list_item(patterns, 1, pattern);
        pattern = read_line(fp);
      }
      fclose(fp);
    } else {
      if (dp) {
        fprintf(stderr, "%s: %s: Is a directory\n", PROGRAM_NAME,
                current_fpatterns->data);
        closedir(dp);
      } else {
        print_error(PROGRAM_NAME, current_fpatterns->data, "");
        errno = 0;
      }
    }
    current_fpatterns = current_fpatterns->next;
  }
}

int scan_color_flags(char** argv, int i) {
  int return_value = 0;
  if (!strcmp("--color", argv[i]) || !strcmp("--colour", argv[i]) ||
      !strcmp("--color=auto", argv[i]) || !strcmp("--colour=auto", argv[i]) ||
      !strcmp("--color=always", argv[i]) ||
      !strcmp("--colour=always", argv[i])) {
    return_value = 1;
  } else if (!strcmp("--color=never", argv[i]) ||
             !strcmp("--colour=never", argv[i])) {
    return_value = 2;
  }
  return return_value;
}

void no_file_name(s_list_t* paths, const s_list_t* patterns) {
  if (!paths->count && patterns->count) {
    insert_list_item(paths, 1, "-");
  }
}

void print_error(const char* program_name, const char* file_name,
                 const char* message) {
  char error_message[BUFFER_SIZE] = {'\0'};
  sprintf(error_message, "%s: %s%s", program_name, file_name, message);
  perror(error_message);
}

void clean_pointer(void* ptr) {
  if (ptr) {
    free(ptr);
  }
}

void* ptr_realloc(void* data, size_t* data_size, size_t type_size) {
  size_t newsize = *data_size * 2;
  void* new_data = realloc(data, newsize * type_size);
  if (new_data == NULL) {
    free(data);
    data = NULL;
    *data_size = 0;
    return (NULL);
  }
  data = new_data;
  *data_size = newsize;
  return data;
}

char* read_line(FILE* fp) {
  size_t i = 0;
  size_t str_size = 8;
  char* str = (char*)calloc(str_size, sizeof(char));
  while ((str[i] = fgetc(fp)) != '\n' && str[i] != EOF) {
    if (i > str_size - 2) {
      str = ptr_realloc(str, &str_size, sizeof(char));
    }
    ++i;
  }
  if (i > str_size - 2) {
    str = ptr_realloc(str, &str_size, sizeof(char));
  }
  if (str[i] == '\n') {
    ++i;
  }
  str[i] = '\0';
  return str;
}

void print_regerror(int errnum, regex_t regex) {
  char error_message[BUFFER_SIZE];
  regerror(errnum, &regex, error_message, BUFFER_SIZE);
  fprintf(stderr, "%s\n", error_message);
}

size_t* search_regex(char* str, const s_list_t* patterns, size_t* index,
                     const s_options_t* flags) {
  regmatch_t pmatch[1];
  size_t size_app = 8;
  size_t* app = (size_t*)calloc(size_app, sizeof(size_t));
  int errnum;
  s_list_item_t* current_pattern = patterns->head;
  while (current_pattern) {
    regex_t regex;
    char* pstr = str;
    if (flags->i && flags->E) {
      errnum = regcomp(&regex, current_pattern->data,
                       REG_NEWLINE | REG_ICASE | REG_EXTENDED);
    } else if (flags->i) {
      errnum = regcomp(&regex, current_pattern->data, REG_NEWLINE | REG_ICASE);
    } else if (flags->E) {
      errnum =
          regcomp(&regex, current_pattern->data, REG_NEWLINE | REG_EXTENDED);
    } else {
      errnum = regcomp(&regex, current_pattern->data, REG_NEWLINE);
    }
    if (errnum) {
      print_regerror(errnum, regex);
      break;
    }
    do {
      if (!regexec(&regex, pstr, 1, pmatch, 0)) {
        if (*index == size_app) {
          size_app *= 2;
          app = ptr_realloc(app, &size_app, sizeof(size_t));
        }
        app[(*index)++] = (size_t)(pmatch[0].rm_so + pstr - str);
        app[(*index)++] = (size_t)(pmatch[0].rm_eo + pstr - str);
        pstr += pmatch[0].rm_eo;
      } else {
        pmatch[0].rm_so = 0;
        pmatch[0].rm_eo = 0;
      }
    } while (pmatch[0].rm_so != pmatch[0].rm_eo);
    current_pattern = current_pattern->next;
    regfree(&regex);
  }
  return app;
}

void print_line(const char* str, const size_t* app, size_t index,
                const s_chcolor_t* colors, const s_options_t* flags) {
  char* mask = (char*)calloc(strlen(str) + 1, sizeof(char));
  for (size_t i = 0; i != index; i += 2) {
    for (size_t j = 0; j != strlen(str); ++j) {
      if (j >= app[i] && j < app[i + 1]) {
        mask[j] = '+';
      } else if (mask[j] != '+') {
        mask[j] = '-';
      }
    }
  }
  for (size_t i = 0; i != strlen(mask); ++i) {
    if (mask[i] == '+') {
      if (flags->color) {
        printf("\033[3%dm%c\033[0m", colors->pn_color, str[i]);
      } else {
        printf("%c", str[i]);
      }
    } else {
      printf("%c", str[i]);
    }
  }
  clean_pointer(mask);
}

void search_patterns(FILE* fp, const s_list_t* patterns, const s_list_t* paths,
                     char* file_name, const s_options_t* flags) {
  s_chcolor_t colors = {1, 5, 6, 2};
  size_t index = 0;
  char* str = NULL;
  size_t* app = NULL;
  int count_lines = 0;
  int count_matches = 0;
  do {
    clean_pointer(str);
    str = read_line(fp);
    ++count_lines;
    app = search_regex(str, patterns, &index, flags);
    if (flags->c || flags->l) {
      if ((flags->v && !index && str[0] != '\0') || (!flags->v && index)) {
        ++count_matches;
        if (flags->l) {
#ifdef __APPLE__
          if (flags->c) {
            c_option(flags, paths, file_name, &count_matches, &colors);
          }
#endif
          l_option(flags, &colors, file_name);
          if (fp) {
            fclose(fp);
            fp = NULL;
          }
          break;
        }
      }
    } else if (flags->o && !flags->v) {
      o_option(str, app, index, count_lines, &colors, flags, paths, file_name);
    } else {
      if (!flags->v && str[0] != '\0' && index) {
        e_option(flags, str, paths, &colors, file_name, index, count_lines,
                 app);
      } else if (flags->v && !flags->o && !index && str[0] != '\0') {
        v_option(flags, str, paths, &colors, file_name, count_lines);
      }
    }
    clean_pointer(app);
    index = 0;
  } while (str[strlen(str) - 1] == '\n');
  clean_pointer(str);
  if (!flags->l) {
    c_option(flags, paths, file_name, &count_matches, &colors);
  }
}

void output(const s_options_t* flags, const s_list_t* patterns,
            const s_list_t* paths) {
  s_list_item_t* current_file = paths->head;
  FILE* fp = NULL;
  DIR* dp = NULL;
  errno = 0;
  for (int i = 1; i <= paths->count; ++i) {
    if (!strcmp(current_file->data, "-") || !strcmp(current_file->data, "")) {
      fp = freopen("/dev/tty", "r", stdin);
    } else {
      fp = fopen(current_file->data, "r");
      dp = opendir(current_file->data);
    }
    if (fp) {
      search_patterns(fp, patterns, paths, current_file->data, flags);
      if (!flags->l) {
        fclose(fp);
        fp = NULL;
      }
    } else if (!flags->s) {
      if (dp) {
        fprintf(stderr, "%s: %s: Is a directory\n", PROGRAM_NAME,
                current_file->data);
        closedir(dp);
      } else {
        print_error(PROGRAM_NAME, current_file->data, "");
        errno = 0;
      }
    }
    if (current_file->next) {
      current_file = current_file->next;
    }
  }
}

void n_option(const s_options_t* flags, const int* count_lines,
              const s_chcolor_t* colors) {
  if (flags->n) {
    if (flags->color) {
      printf("\033[3%dm%d\033[0m", colors->number_line_color, *count_lines);
      printf("\033[3%dm:\033[0m", colors->colon_color);
    } else {
      printf("%d:", *count_lines);
    }
  }
}

void c_option(const s_options_t* flags, const s_list_t* paths, char* file_name,
              const int* count_matches, const s_chcolor_t* colors) {
  char* pfn = file_name;
  if (flags->c) {
    if ((paths->count == 1 && !flags->H) || flags->h) {
      printf("%d\n", *count_matches);
    } else if ((paths->count > 1 && !flags->h) || flags->H) {
      if (!strcmp(file_name, "-")) {
        pfn = "(standard input)";
      }
      if (flags->color) {
        printf("\033[3%dm%s\033[0m", colors->fn_color, pfn);
        printf("\033[3%dm:\033[0m", colors->colon_color);
        printf("%d\n", *count_matches);
      } else {
        printf("%s:%d\n", pfn, *count_matches);
      }
    }
  }
}

void e_option(const s_options_t* flags, const char* str, const s_list_t* paths,
              const s_chcolor_t* colors, char* file_name, size_t index,
              int count_lines, const size_t* app) {
  char* pfn = file_name;
  if ((paths->count == 1 && !flags->H) || flags->h) {
    n_option(flags, &count_lines, colors);
    print_line(str, app, index, colors, flags);
  } else if ((paths->count > 1 && !flags->h) || flags->H) {
    if (!strcmp(file_name, "-")) {
      pfn = "(standard input)";
    }
    if (flags->color) {
      printf("\033[3%dm%s\033[0m", colors->fn_color, pfn);
      printf("\033[3%dm:\033[0m", colors->colon_color);
    } else {
      printf("%s:", pfn);
    }
    n_option(flags, &count_lines, colors);
    print_line(str, app, index, colors, flags);
  }
}

void v_option(const s_options_t* flags, const char* str, const s_list_t* paths,
              const s_chcolor_t* colors, char* file_name, int count_lines) {
  char* pfn = file_name;
  if ((paths->count == 1 && !flags->H) || flags->h) {
    n_option(flags, &count_lines, colors);
    printf("%s", str);
  } else if ((paths->count > 1 && !flags->h) || flags->H) {
    if (!strcmp(file_name, "-")) {
      pfn = "(standard input)";
    }
    if (flags->color) {
      printf("\033[3%dm%s\033[0m", colors->fn_color, pfn);
      printf("\033[3%dm:\033[0m", colors->colon_color);
    } else {
      printf("%s:", pfn);
    }
    n_option(flags, &count_lines, colors);
    printf("%s", str);
  }
}

void o_option(const char* str, size_t* app, size_t index, int count_lines,
              const s_chcolor_t* colors, const s_options_t* flags,
              const s_list_t* paths, char* file_name) {
  for (size_t i = 0; i != index; i += 2) {
    for (size_t j = i + 2; j != index; j += 2) {
      if (app[i] > app[j]) {
        size_t tmp1 = app[i];
        size_t tmp2 = app[i + 1];
        app[i] = app[j];
        app[i + 1] = app[j + 1];
        app[j] = tmp1;
        app[j + 1] = tmp2;
      }
    }
  }
  for (size_t i = 0; i != index; i += 2) {
    char* pfn = file_name;
    if ((paths->count == 1 && !flags->H) || flags->h) {
      n_option(flags, &count_lines, colors);
      print_pattern(str, app, i, flags, colors);
    } else if ((paths->count > 1 && !flags->h) || flags->H) {
      if (!strcmp(file_name, "-")) {
        pfn = "(standard input)";
      }
      if (flags->color) {
        printf("\033[3%dm%s\033[0m", colors->fn_color, pfn);
        printf("\033[3%dm:\033[0m", colors->colon_color);
      } else {
        printf("%s:", pfn);
      }
      n_option(flags, &count_lines, colors);
      print_pattern(str, app, i, flags, colors);
    }
#ifdef __APPLE__
    if (i > 1) {
      print_pattern(str, app, i, flags, colors);
    }
#endif
  }
}

void print_pattern(const char* str, const size_t* app, size_t i,
                   const s_options_t* flags, const s_chcolor_t* colors) {
  for (size_t j = 0; j != strlen(str); ++j) {
    if (j >= app[i] && j < app[i + 1]) {
      if (flags->color) {
        printf("\033[3%dm%c\033[0m", colors->pn_color, str[j]);
      } else {
        printf("%c", str[j]);
      }
    }
  }
  putchar('\n');
}

void l_option(const s_options_t* flags, const s_chcolor_t* colors,
              char* file_name) {
  char* pfn = file_name;
  if (!strcmp(file_name, "-")) {
    pfn = "(standard input)";
  }
  if (flags->color) {
    printf("\033[3%dm%s\033[0m\n", colors->fn_color, pfn);
  } else {
    printf("%s\n", pfn);
  }
}

// void print_lists(s_list_t* patterns, s_list_t* fpatterns, s_list_t* paths) {
//   printf("Patterns:");
//   print_list(patterns);
//   printf("\nFpatterns:");
//   print_list(fpatterns);
//   printf("\nFiles:");
//   print_list(paths);
//   putchar('\n');
// }
