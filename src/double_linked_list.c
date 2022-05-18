#include <stdlib.h>

#include "nds_double_linked_list.h"

nds_dllist_node_t *nds_dllist_node_new(void *value) {
  nds_dllist_node_t *node =
      (nds_dllist_node_t *)malloc(sizeof(nds_dllist_node_t));

  node->prev = NULL;
  node->next = NULL;
  node->data = value;

  return node;
}

void nds_dllist_node_free(nds_dllist_node_t *node) {
  free(node);
}

size_t nds_dllist_push(nds_dllist_t *list, nds_dllist_node_t *node) {
  if (list->tail)
    list->tail->next = node;
  else
    list->head = node;

  node->prev = list->tail;
  list->tail = node;

  return ++list->length;
}

nds_dllist_node_t *nds_dllist_pop(nds_dllist_t *list) {
  nds_dllist_node_t *popped = list->tail;
  nds_dllist_remove(list, list->tail);

  return popped;
}

nds_dllist_node_t *nds_dllist_remove(nds_dllist_t *list, nds_dllist_node_t *node) {
  if (node == list->head)
    list->head = node->next;
  else if (node->prev)
    node->prev->next = node->next;

  if (node == list->tail)
    list->tail = node->prev;
  else if (node->next)
    node->next->prev = node->prev;

  node->next = NULL;
  node->prev = NULL;

  list->length--;

  return node;
}
