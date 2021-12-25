#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define vectorpush(vec) ((typeof(vec))vector_push((void **)&vec))

void *vector_new(size_t cap, size_t elem_size);

size_t vector_len(void *);
size_t vector_cap(void *);
bool vector_isfull(void *);
bool vector_isemtpy(void *);

void *vector_push(void **vec);
void vector_pop(void *);
void vector_shift(void *);

void vector_free(void *);

#endif