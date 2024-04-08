/**
 * \file compute.h
 **/

#ifndef TOP_COMPUTE_H
#define TOP_COMPUTE_H

#include "../../types.h"

/**
 * \brief Allocate, compute $c = a + b$, print results and elapsed time.
 *
 * \param vector_size Size of all vectors.
 * \param repetitions Number of repetitions to get meaningful duration.
 **/
void compute(uint32_t vector_size, uint32_t repetitions);

#endif // TOP_COMPUTE_H
