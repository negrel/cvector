#ifndef NDS_VECTOR_H
#define NDS_VECTOR_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef void *nds_vector_t;

// nds_vector_foreach is a foreach macro for the vector type.
// The first parameter is the vector on which to iterate. The
// second is the name of the iterator. The index is accessible
// with `iterator.index` and the value with `iterator.value`.
#define nds_vector_foreach(vec, iterator) \
  for (struct { size_t index; typeof(*vec) value; } iterator = { .value = vec[0] }; iterator.index < nds_vector_len(vec); iterator.value = vec[++iterator.index])

// nds_vector_push returns a pointer to an element at the end of the vector.
// This function takes a double pointer to a vector to reallocate it's full.
#define nds_vector_push(vec) ((typeof(*vec))nds_vector_push_((void **)vec))

// nds_vector_unshift adds an element at the beginning of the vector and shift
// other elements.
#define nds_vector_unshift(vec) ((typeof(*vec))nds_vector_unshift_((void **)vec))

// nds_vector_new returns a new zeroed vector with the given capacity to store
// element of the given size. It the returns a pointer to the first element of
// the vector.
nds_vector_t nds_vector_new(size_t cap, size_t elem_size);

// nds_vector_clone creates a clone of the given vector and returns it.
nds_vector_t nds_vector_clone(nds_vector_t);

// nds_vector_len returns the current len of the vector.
size_t nds_vector_len(nds_vector_t);

// nds_vector_cap returns the current capacity of the vector.
size_t nds_vector_cap(nds_vector_t);

// nds_vector_isfull returns true if the vector is full.
bool nds_vector_isfull(nds_vector_t);

// nds_vector_isempty returns true if the vector size is 0.
bool nds_vector_isemtpy(nds_vector_t);

// nds_vector_push_ returns a pointer to an element at the end of the vector.
// This function takes a pointer to a vector to reallocate it if it's full.
// An handy vector_push macro exists so you don't have to cast arguments and
// return type.
void *nds_vector_push_(nds_vector_t *);

// nds_vector_pop removes the last element of the vector and store it in popped if
// not null.
void nds_vector_pop(nds_vector_t, void *);

// nds_vector_shift removes the first element of the vector and store it shifted if
// not null. Remaining elements are copied to their index - 1.
void nds_vector_shift(nds_vector_t, void *);

// nds_vector_unshift_ adds an element at the beginning of the vector and shift
// other elements.
// An handy vector_unshift macro exists so you don't have to cast arguments and
// return type.
void *nds_vector_unshift_(nds_vector_t *);

// vector_free free the given vector.
void nds_vector_free(void *);

#endif