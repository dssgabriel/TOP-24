/**
 * \file compute.c
 * \brief Allocate, add vectors and print results.
 **/

#include "compute.h"

#include "timer.h"
#include "vector.h"

#include <stdio.h>

/**
 * \brief Print vectors to check if $a + b = c$.
 *
 * \param a First source vector.
 * \param b Second source vector.
 * \param c Destination vector.
 * \param n Size of all vectors.
 **/
static void
print_results(uint32_t n, uint32_t const a[n], uint32_t const b[n], uint32_t const c[n]) {
    puts("*******************************************************");
    puts("\ta\t+\tb\t=\tc");
    puts("-------------------------------------------------------");
    for (uint32_t i = 0; i < n; ++i) {
        printf("\t%u\t \t%u\t \t%u\n", a[i], b[i], c[i]);
    }
}

void compute(uint32_t vector_size, uint32_t repetitions) {
    TIMER_INIT

    uint32_t* a = allocate_vector(vector_size);
    uint32_t* b = allocate_vector(vector_size);
    uint32_t* c = allocate_vector(vector_size);

    // Initialize each vector
    init_vector(vector_size, a, 1);
    init_vector(vector_size, b, 2);
    init_vector(vector_size, c, 0);

    // c = a + b
    TIMER_START
    for (uint32_t i = 0; i < repetitions; ++i) {
        add_vectors(vector_size, c, a, b);
    }
    TIMER_END

    TIMER_PRINT
    print_results(vector_size, a, b, c);

    free_vector(&c);
    free_vector(&b);
    free_vector(&a);
    puts("*******************************************************");
}
