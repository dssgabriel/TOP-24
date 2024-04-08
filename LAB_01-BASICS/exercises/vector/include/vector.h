/**
 * \file vector.h
 **/

#ifndef TOP_VECTOR_H
#define TOP_VECTOR_H

#include "../../types.h"

/**
 * \brief Allocate a vector with the specified size.
 *
 * \param size Size of the vector to allocate.
 * \return Pointer to the allocated vector.
 **/
uint32_t* allocate_vector(uint32_t size);

/**
 * \brief Free an allocated vector and set its pointer to `NULL`.
 *
 * \param vector Pointer of pointer to the vector.
 **/
void free_vector(uint32_t** vector);

/**
 * \brief Initialize a vector with a value.
 *
 * \param n Size of the vector.
 * \param vector Vector to initialize.
 * \param value Value to set.
 **/
void init_vector(uint32_t n, uint32_t vector[n], uint32_t value);

/**
 * \brief Add two vectors and store result in a third one.
 *
 * \param n Size of all vectors.
 * \param dest Destination result vector.
 * \param src1 First source vector.
 * \param src2 Second source vector.
 **/
void add_vectors(uint32_t n, uint32_t dest[n], uint32_t const src1[n], uint32_t const src2[n]);

#endif // TOP_VECTOR_H
