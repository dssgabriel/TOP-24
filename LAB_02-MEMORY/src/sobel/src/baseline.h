#pragma once

#include "common.h"

int32_t convolve_baseline(
    uint8_t const* restrict m,
    int32_t const* restrict f,
    size_t fh,
    size_t fw
);

void sobel_baseline(
    uint8_t const* cframe,
    uint8_t* oframe,
    float32_t threshold
);
