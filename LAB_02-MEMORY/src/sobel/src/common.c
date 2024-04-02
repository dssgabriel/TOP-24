#include "common.h"

#include <math.h>

void sort(float64_t* restrict array, size_t len) {
    for (size_t i = 0; i < len; i++) {
        for (size_t j = i + 1; j < len; j++) {
            if (array[i] > array[j]) {
                float64_t tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
        }
    }
}

float64_t mean(float64_t const* restrict array, size_t len) {
    float64_t mean = 0.0;
    for (size_t i = 0; i < len; i++) {
        mean += array[i];
    }
    return mean / (float64_t)(len);
}

float64_t sdev(float64_t const* restrict array, size_t len, float64_t mean) {
    float64_t sdev = 0.0;
    for (size_t i = 0; i < len; i++) {
        sdev += (array[i] - mean) * (array[i] - mean);
    }
    return sqrt(sdev / (float64_t)(len - 1));
}
