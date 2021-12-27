#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define vector_push(vec) ((typeof(*vec))vector_push_((void **)vec))
#define vector_unshift(vec) ((typeof(*vec))vector_unshift_((void **)vec))

void *vector_new(size_t cap, size_t elem_size);
void *vector_clone(void *);

size_t vector_len(void *);
size_t vector_cap(void *);
bool vector_isfull(void *);
bool vector_isemtpy(void *);

void *vector_push_(void **);
void vector_pop(void *, void *);
void vector_shift(void *, void *);
void *vector_unshift_(void **);

void vector_free(void *);

#endif