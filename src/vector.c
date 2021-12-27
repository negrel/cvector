#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/vector.h"

#define container_of(ptr, type, member)                                        \
  ({                                                                           \
    const typeof(((type *)0)->member) *__mptr = (ptr);                         \
    (type *)((char *)__mptr - offsetof(type, member));                         \
  })

#define bodyof(vecptr) ((void *)(vecptr) + sizeof(vector_t))
#define headerof(bodyptr) ((vector_t *)(bodyptr - sizeof(vector_t)))

typedef struct {
  // Header
  size_t cap;
  size_t len;
  size_t elem_size;

  // Body
  // ...
} vector_t;

void *vector_new(size_t cap, size_t elem_size) {
  size_t header = sizeof(vector_t);
  size_t body = cap * elem_size;

  vector_t *vec = calloc(header + body, 1);
  if (vec == NULL)
    return NULL;

  vec->len = 0;
  vec->cap = cap;
  vec->elem_size = elem_size;

  return bodyof(vec);
}

void vector_free(void *vec) {
  assert(vec != NULL);

  vector_t *v = headerof(vec);
  free(v);
}

size_t vector_len(void *vec) {
  assert(vec != NULL);

  return headerof(vec)->len;
}

size_t vector_cap(void *vec) {
  assert(vec != NULL);

  return headerof(vec)->cap;
}

bool vector_isfull(void *vec) {
  assert(vec != NULL);

  return vector_len(vec) == vector_cap(vec);
}

bool vector_isempty(vector_t *vec) {
  assert(vec != NULL);

  return vector_len(vec) == 0;
}

void *vector_push_(void **vec) {
  assert(vec != NULL);
  assert(*vec != NULL);

  if (vector_isfull(*vec)) {
    // Let's double the capacity of our vector
    vector_t *old = headerof(*vec);

    void *new = vector_new(old->cap * 2, old->elem_size);
    headerof(new)->len = old->len;

    memcpy(new, bodyof(old), old->cap * old->elem_size);
    free(old);

    *vec = new;
  }

  vector_t *v = headerof(*vec);
  size_t offset = v->elem_size * v->len;

  v->len++;

  return bodyof(v) + offset;
}

void vector_pop(void *vec, void *popped) {
  assert(vec != NULL);

  if (vector_isempty(vec))
    return;

  vector_t *v = headerof(vec);
  v->len--;

  if (popped != NULL)
    memcpy(popped, vec + v->len * v->elem_size, v->elem_size);
}

void vector_shift(void *vec, void *shifted) {
  assert(vec != NULL);

  if (vector_isempty(vec))
    return;

  vector_t *v = headerof(vec);
  if (shifted != NULL)
    memcpy(shifted, vec, v->elem_size);

  v->len--;

  memmove(bodyof(v), bodyof(v) + v->elem_size, v->len * v->elem_size);
}

void *vector_unshift_(void **vec) {
  assert(vec != NULL);
  assert(*vec != NULL);

  if (vector_isfull(*vec)) {
    // Let's double the capacity of our vector
    vector_t *old = headerof(*vec);

    void *new = vector_new(old->cap * 2, old->elem_size);
    headerof(new)->len = old->len + 1;

    // Copy old elements in new at index 1
    memcpy(new + old->elem_size, bodyof(old), old->cap * old->elem_size);
    free(old);

    *vec = new;

    return new;
  }

  vector_t *v = headerof(*vec);
  // Move all elements by 1
  memmove(*vec + v->elem_size, *vec, v->len * v->elem_size);
  v->len++;

  return *vec;
}