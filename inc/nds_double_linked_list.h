#ifndef NDS_DOUBLE_LINKED_LIST_H
#define NDS_DOUBLE_LINKED_LIST_H

#include <stddef.h>

#define nds_dllist_foreach (list, elem) \
  for (nds_dllist_node_t elem = list->head; elem != NULL; elem = elem->next)

typedef struct nds_dllist_node_t {
  struct nds_dllist_node_t *next;
  struct nds_dllist_node_t *prev;
  void *data;
} nds_dllist_node_t;

nds_dllist_node_t *nds_dllist_node_new(void *value);
void nds_dllist_node_free(nds_dllist_node_t *);

typedef struct {
  nds_dllist_node_t *head;
  nds_dllist_node_t *tail;
  size_t length;
} nds_dllist_t;

size_t nds_dllist_push(nds_dllist_t *list, nds_dllist_node_t *node);

nds_dllist_node_t *nds_dllist_pop(nds_dllist_t *list);

size_t nds_dllist_unshift(nds_dllist_t *list, nds_dllist_node_t *node);

nds_dllist_node_t *nds_dllist_shift(nds_dllist_t *list);

size_t nds_dllist_insert_before(nds_dllist_t *list, nds_dllist_node_t *node,
                                nds_dllist_node_t *reference);

nds_dllist_node_t *nds_dllist_remove(nds_dllist_t *list, nds_dllist_node_t *node);

#endif