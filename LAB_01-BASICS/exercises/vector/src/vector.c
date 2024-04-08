/**
 * \file vector.c
 * \brief Vector operations.
 **/

#include "vector.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t* allocate_vector(uint32_t size) {
    uint32_t* vector = (uint32_t*)malloc(size * sizeof(uint32_t));
    assert(NULL != vector);
    return vector;
}

void free_vector(uint32_t** vector) {
    free(*vector);
    *vector = NULL;
}

void init_vector(uint32_t n, uint32_t vector[n], uint32_t value) {
    for (uint32_t i = 0; i < n; ++i) {
        vector[i] = value;
    }
}

void add_vectors(uint32_t n, uint32_t dest[n], uint32_t const src1[n], uint32_t const src2[n]) {
    for (uint32_t i = 0; i < n; ++i) {
        dest[i] = src1[i] + src2[i];
    }
}
