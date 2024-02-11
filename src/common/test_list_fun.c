#include "s21_list_functions.h"

int main(void) {
  s_list_t* list = NULL;
  s_list_item_t* new_item = NULL;
  char* str = NULL;

  list = create_list();
  insert_list_item(list, -1, "one");
  insert_list_item(list, -1, "two");
  insert_list_item(list, -1, "three");
  insert_list_item(list, -1, "four");
  insert_list_item(list, -1, "five");

  printf("\nTest insert_line_item() and print_list():");
  print_list(list);

  printf("\nTest get_list_item():\n");
  for (int i = 1; i < list->count + 1; ++i) {
    new_item = get_list_item(list, i);
    printf("item_%d->data = %s\n", i, new_item->data);
  }
  new_item = get_list_item(list, 8);

  printf("\nTest read_list_item():\n");
  for (int i = 1; i < list->count + 1; ++i) {
    str = read_list_item(list, i);
    printf("index = %d  str = %s\n", i, str);
  }
  str = read_list_item(list, 7);

  printf("\nTest search_list_item():\n");
  for (int i = 1; i <= list->count; ++i) {
    str = read_list_item(list, i);
    printf("index = %d\n", search_list_item(list, str));
  }
  printf("index = %d\n", search_list_item(list, "simsim-sezam"));

  printf("\nTest delete_list_item():");
  delete_list_item(list, 1);
  print_list(list);

  printf("\nTest delete_list():");
  delete_list(list);
  print_list(list);

  return 0;
}
