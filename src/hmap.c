#include "hmap.h"

typedef struct {

} bucket_t;

size_t nds_hash_bytes(const void *data, size_t data_size) {
  siphash(const void *in, const size_t inlen, const void *k, uint8_t *out, const size_t outlen);
}

void nds_hmap_init(nds_hmap_t *hmap, nds_hash_fn_t hash) {
  hmap->vector = nds_vector_new(128, elem_size);
  hmap->hash_fn = NULL;
}

void nds_hmap_deinit(nds_hmap_t *hmap) {
  nds_vector_free(hmap->vector);
}
