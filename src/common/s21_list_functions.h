#ifndef S21_LIST_FUNCTIONS_H
#define S21_LIST_FUNCTIONS_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct doubly_linked_list_item {
  char *data;
  struct doubly_linked_list_item *next;
  struct doubly_linked_list_item *prev;
} s_list_item_t;

typedef struct {
  int count;
  s_list_item_t *head;
  s_list_item_t *tail;
} s_list_t;

s_list_t *create_list();
s_list_item_t *insert_list_item(s_list_t *list, int index, char *str);
char *read_list_item(s_list_t *list, int index);
int search_list_item(s_list_t *list, char *data);
s_list_item_t *get_list_item(s_list_t *list, int index);
void delete_list_item(s_list_t *list, int index);
void delete_list(s_list_t *list);
void print_list(s_list_t *list);

#endif
