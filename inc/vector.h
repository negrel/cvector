#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// vector_push_ returns a pointer to an element at the end of the vector.
// This function takes a double pointer to a vector to reallocate it's full.
#define vector_push(vec) ((typeof(*vec))vector_push_((void **)vec))

// vector_unshift_ adds an element at the beginning of the vector and shift
// other elements.
#define vector_unshift(vec) ((typeof(*vec))vector_unshift_((void **)vec))

// vector_new returns a new zeroed vector with the given capacity to store
// element of the given size. It the returns a pointer to the first element of
// the vector.
void *vector_new(size_t cap, size_t elem_size);

// vector_clone clones the given vector and returns it.
void *vector_clone(void *vec);

// vector_len returns the current len of the vector.
size_t vector_len(void *);

// vector_cap returns the current capacity of the vector.
size_t vector_cap(void *);

// vector_isfull returns true if the vector is full.
bool vector_isfull(void *);

// vector_isempty returns true if the vector size is 0.
bool vector_isemtpy(void *);

// vector_push_ returns a pointer to an element at the end of the vector.
// This function takes a double pointer to a vector to reallocate it's full.
// An handy vector_push macro exists so you don't have to cast arguments and
// return type.
void *vector_push_(void **);

// vector_pop removes the last element of the vector and store it in popped if
// not null.
void vector_pop(void *, void *);

// vector_shift removes the first element of the vector and store it shifted if
// not null. Remaining elements are copied to their index - 1.
void vector_shift(void *, void *);

// vector_unshift_ adds an element at the beginning of the vector and shift
// other elements.
// An handy vector_unshift macro exists so you don't have to cast arguments and
// return type.
void *vector_unshift_(void **);

// vector_free free the given vector.
void vector_free(void *);

#endif