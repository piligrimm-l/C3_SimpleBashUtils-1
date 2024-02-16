#include "s21_list_functions.h"

s_list_t *create_list() {
  s_list_t *list = (s_list_t *)calloc(1, sizeof(s_list_t));
  list->count = 0;
  list->head = NULL;
  list->tail = NULL;
  return list;
}

s_list_item_t *insert_list_item(s_list_t *list, int index, char *data) {
  int size = strlen(data);
  s_list_item_t *new_item = (s_list_item_t *)calloc(1, sizeof(s_list_item_t));
  new_item->data = (char *)calloc(size + 1, sizeof(char));
  strncpy(new_item->data, data, size);
  if (!list->count) {
    new_item->prev = NULL;
    new_item->next = NULL;
    list->head = new_item;
    list->tail = new_item;
  } else if (index < 0) {
    new_item->next = list->head;
    list->head = new_item;
    new_item->prev = NULL;
    new_item->next->prev = new_item;
  } else if (index > 0) {
    new_item->next = NULL;
    new_item->prev = list->tail;
    list->tail = new_item;
    new_item->prev->next = new_item;
  }
  ++list->count;
  return new_item;
}

s_list_item_t *get_list_item(s_list_t *list, int index) {
  s_list_item_t *current = NULL;
  int middle = list->count / 2;
  if (index >= middle) {
    current = list->tail;
    for (int i = list->count; i > index; --i) {
      current = current->prev;
    }
  } else if (index < middle) {
    current = list->head;
    for (int i = 1; i < index; ++i) {
      current = current->next;
    }
  }
  if (current == NULL || index < 0 || index > list->count) {
    printf("Error! The list_item with index = %d was not found...\n", index);
  }
  return current;
}

char *read_list_item(s_list_t *list, int index) {
  s_list_item_t *current = get_list_item(list, index);
  return current->data;
}

int search_list_item(s_list_t *list, char *data) {
  int index = 0;
  s_list_item_t *current = list->head;
  for (index = 1; strcmp(data, current->data) && index <= list->count;
       ++index) {
    if (current->next) {
      current = current->next;
    }
  }
  return index <= list->count ? index : -1;
}

void print_list(s_list_t *list) {
  s_list_item_t *current = list->head;
  puts("\n\033[44m***Printing a list***\033[0m");
  if (!list->head) {
    puts("\033[32mThe list empty\033[0m");
  } else {
    for (int i = 1; current != NULL; ++i) {
      printf("Index: %d || Data: %s\n", i, current->data);
      current = current->next;
    }
  }
}

void delete_list_item(s_list_t *list, int index) {
  s_list_item_t *current = get_list_item(list, index);
  if (current == NULL || index < 1 || index > list->count) {
    return;
  }

  if (current->prev) {
    current->prev->next = current->next;
  }
  if (current->next) {
    current->next->prev = current->prev;
  }

  if (!current->prev) {
    list->head = current->next;
  }
  if (!current->next) {
    list->tail = current->prev;
  }

  current->prev = current->next = NULL;
  if (current) {
    free(current->data);
    current->data = NULL;
    free(current);
    current = NULL;
  }
  --list->count;
}

void delete_list(s_list_t *list) {
  if (list->head) {
    do {
      s_list_item_t *current = list->head;
      list->head = list->head->next;
      free(current->data);
      current->data = NULL;
      free(current);
      current = NULL;
      --list->count;
    } while (list->count);
  }
  if (list) {
    free(list);
    list = NULL;
  }
}
