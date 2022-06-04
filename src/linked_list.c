#include <stdlib.h>

#include "linked_list.h"

nds_llist_node_t *nds_llist_node_new(void *value) {
  nds_llist_node_t *node =
      (nds_llist_node_t *)malloc(sizeof(nds_llist_node_t));

  node->next = NULL;
  node->data = value;

  return node;
}

void nds_llist_node_free(nds_llist_node_t *node) {
  free(node);
}
