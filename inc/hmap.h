#ifndef HMAP_H
#define HMAP_H

#include "vector.h"

typedef struct {
  nds_hmap_fn_t *hash_fn;
  nds_vector_t *vector;
} nds_hmap_t;

typedef size_t (*nds_hash_fn_t)(void *, size_t);

size_t nds_hash_bytes(void *data, size_t data_size, size_t data_length);

void nds_hmap_init(nds_hmap_t *hmap, nds_hash_fn_t hash);

#endif