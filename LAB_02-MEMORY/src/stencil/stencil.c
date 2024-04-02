#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

size_t N = 16384;
size_t M = 16384;

void now(struct timespec* t) {
    clock_gettime(CLOCK_MONOTONIC_RAW, t);
}

double duration_ms(struct timespec t0, struct timespec t1) {
    return (t1.tv_sec - t0.tv_sec) * 1.0e+3 + (t1.tv_nsec - t0.tv_nsec) * 1.0e-6;
}

void stencil(size_t n, size_t m, double const* in, double* out) {
#pragma omp parallel for
    for (size_t i = 1; i < n + 1; ++i) {
        for (size_t j = 1; j < m + 1; ++j) {
            out[i * m + j] = in[(i - 1) * m + j] + in[i * m + (j - 1)] + in[i * m + j]
                             + in[i * m + (j + 1)] + in[(i + 1) * m + j];
            out[i * m + j] /= in[i * m + j];
        }
    }
}

int main(int argc, char* argv[]) {
    printf("%zux%zu\n", N, M);

    fprintf(stderr, "alloc...\r");
    double* a = calloc((N + 2) * (M + 2), sizeof(double));
    double* b = calloc((N + 2) * (M + 2), sizeof(double));
    fprintf(stderr, "setup...\r");

#pragma omp parallel for collapse(2)
    for (size_t i = 1; i < N + 1; ++i) {
        for (size_t j = 1; j < M + 1; ++j) {
            a[i * M + j] = drand48();
        }
    }

    struct timespec t0, t1;
    double elapsed;

    fprintf(stderr, "warm normal...\r");
    stencil(N, M, a, b);
    fprintf(stderr, "bench normal...\r");
    now(&t0);
    stencil(N, M, a, b);
    now(&t1);
    elapsed = duration_ms(t0, t1);
    printf("normal:  %.3lf ms\n", elapsed);

    return 0;
}
