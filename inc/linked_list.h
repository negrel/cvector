#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct nds_llist_node_t {
  struct nds_llist_node_t *next;
  void *data;
} nds_llist_node_t;

nds_llist_node_t *nds_llist_node_new(void *value);
void nds_llist_node_free(nds_llist_node_t *);

typedef struct {
  nds_llist_node_t *head;
  nds_llist_node_t *tail;
  size_t length;
} nds_llist_t;



#endif