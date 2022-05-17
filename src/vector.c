#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "nds_vector.h"

#define container_of(ptr, type, member)                                        \
  ({                                                                           \
    const typeof(((type *)0)->member) *__mptr = (ptr);                         \
    (type *)((char *)__mptr - offsetof(type, member));                         \
  })

#define bodyof(vecptr) ((void *)(vecptr) + sizeof(struct vector))
#define headerof(bodyptr) ((struct vector *)(bodyptr - sizeof(struct vector)))

struct vector {
  // Header
  size_t cap;
  size_t len;
  size_t elem_size;

  // Body
  // ...
};

vector_t nds_vector_new(size_t cap, size_t elem_size) {
  size_t header = sizeof(struct vector);
  size_t body = cap * elem_size;

  struct vector *vec = calloc(header + body, 1);
  if (vec == NULL)
    return NULL;

  vec->len = 0;
  vec->cap = cap;
  vec->elem_size = elem_size;

  return bodyof(vec);
}

static size_t sizeof_vector(struct vector *v) {
  return sizeof(struct vector) + v->cap * v->elem_size;
}

vector_t nds_vector_clone(vector_t vec) {
  assert(vec != NULL);

  struct vector *v = headerof(vec);
  size_t size_v = sizeof_vector(v);

  void *clone = malloc(size_v);
  if (clone == NULL)
    return NULL;

  memcpy(clone, v, size_v);

  return bodyof(clone);
}

void nds_vector_free(vector_t vec) {
  assert(vec != NULL);

  struct vector *v = headerof(vec);
  free(v);
}

size_t nds_vector_len(vector_t vec) {
  assert(vec != NULL);

  return headerof(vec)->len;
}

size_t nds_vector_cap(vector_t vec) {
  assert(vec != NULL);

  return headerof(vec)->cap;
}

bool nds_vector_isfull(vector_t vec) {
  assert(vec != NULL);

  return nds_vector_len(vec) == nds_vector_cap(vec);
}

bool nds_vector_isempty(vector_t *vec) {
  assert(vec != NULL);

  return nds_vector_len(vec) == 0;
}

void *nds_vector_push_(void **vec) {
  assert(vec != NULL);
  assert(*vec != NULL);

  if (nds_vector_isfull(*vec)) {
    // Let's double the capacity of our vector
    struct vector *old = headerof(*vec);

    void *new = nds_vector_new(old->cap * 2, old->elem_size);
    headerof(new)->len = old->len;

    memcpy(new, bodyof(old), old->cap * old->elem_size);
    free(old);

    *vec = new;
  }

  struct vector *v = headerof(*vec);
  size_t offset = v->elem_size * v->len;

  v->len++;

  return bodyof(v) + offset;
}

void nds_vector_pop(vector_t vec, void *popped) {
  assert(vec != NULL);

  if (nds_vector_isempty(vec))
    return;

  struct vector *v = headerof(vec);
  v->len--;

  if (popped != NULL)
    memcpy(popped, vec + v->len * v->elem_size, v->elem_size);
}

void nds_vector_shift(vector_t vec, void *shifted) {
  assert(vec != NULL);

  if (nds_vector_isempty(vec))
    return;

  struct vector *v = headerof(vec);
  if (shifted != NULL)
    memcpy(shifted, vec, v->elem_size);

  v->len--;

  memmove(bodyof(v), bodyof(v) + v->elem_size, v->len * v->elem_size);
}

void *nds_vector_unshift_(void **vec) {
  assert(vec != NULL);
  assert(*vec != NULL);

  if (nds_vector_isfull(*vec)) {
    // Let's double the capacity of our vector
    struct vector *old = headerof(*vec);

    void *new = nds_vector_new(old->cap * 2, old->elem_size);
    headerof(new)->len = old->len + 1;

    // Copy old elements in new at index 1
    memcpy(new + old->elem_size, bodyof(old), old->cap * old->elem_size);
    free(old);

    *vec = new;

    return new;
  }

  struct vector *v = headerof(*vec);
  // Move all elements by 1
  memmove(*vec + v->elem_size, *vec, v->len * v->elem_size);
  v->len++;

  return *vec;
}