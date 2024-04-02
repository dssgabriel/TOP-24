#include "baseline.h"

#include "common.h"

#include <math.h>

int32_t
convolve_baseline(uint8_t const* restrict m, int32_t const* restrict f, size_t fh, size_t fw) {
    int32_t r = 0;
    for (size_t i = 0; i < fh; i++) {
        for (size_t j = 0; j < fw; j++) {
            r += m[idx2d(i, j * 3, WIDTH * 3)] * f[idx2d(i, j, fw)];
        }
    }
    return r;
}

void sobel_baseline(uint8_t const* cframe, uint8_t* oframe, float32_t threshold) {
    int32_t f1[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 }; // 3x3 matrix
    int32_t f2[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 }; // 3x3 matrix

    for (size_t i = 0; i < (HEIGHT - 3); i++) {
        for (size_t j = 0; j < ((WIDTH * 3) - 3); j++) {
            int32_t gx = convolve_baseline(&cframe[idx2d(i, j, WIDTH * 3)], f1, 3, 3);
            int32_t gy = convolve_baseline(&cframe[idx2d(i, j, WIDTH * 3)], f2, 3, 3);
            float32_t mag = sqrtf((float32_t)((gx * gx) + (gy * gy)));
            oframe[idx2d(i, j, WIDTH * 3)] = (mag > threshold) ? (uint8_t)(255) : (uint8_t)(mag);
        }
    }
}
