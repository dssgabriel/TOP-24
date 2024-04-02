/**
 * This code performs edge detection using a Sobel filter on a video stream
 * meant as input to a neural network.
 **/

#include "baseline.h"
#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static size_t const ALIGNMENT = 64;

/// Converts an image to its grayscale equivalent - better color precision.
static void grayscale_weighted(uint8_t* restrict frame) {
    for (size_t i = 0; i < HEIGHT * WIDTH * 3; i += 3) {
        // Convert RGB color values into grayscale for each pixel using color
        // weights Other possible weights: 0.59, 0.30, 0.11 Principle: mix different
        // quantities of R, G, B to create a variant of gray
        float32_t gray = 0.299F * (float32_t)(frame[i]) + 0.587F * (float32_t)(frame[i + 1])
                         + 0.114F * (float32_t)(frame[i + 2]);
        frame[i] = (uint8_t)(gray);
        frame[i + 1] = (uint8_t)(gray);
        frame[i + 2] = (uint8_t)(gray);
    }
}

int32_t main(int32_t argc, char* argv[argc + 1]) {
    if (argc < 3) {
        return fprintf(stderr, "Usage: %s <input.raw> <output.raw>\n", argv[0]), EXIT_FAILURE;
    }

    // Size of a frame
    size_t size = sizeof(uint8_t) * HEIGHT * WIDTH * 3;
    uint8_t** frames = aligned_alloc(ALIGNMENT, MAX_SAMPLES * sizeof(uint8_t*));
    if (frames == NULL) {
        return fprintf(stderr, "error: failed to allocate `frames` memory\n"), EXIT_FAILURE;
    }
    for (size_t i = 0; i < MAX_SAMPLES; ++i) {
        frames[i] = aligned_alloc(ALIGNMENT, size);
        if (frames[i] == NULL) {
            return fprintf(stderr, "error: failed to allocate `frames[%zu]` memory\n", i),
                   EXIT_FAILURE;
        }
    }

    FILE* fpi = fopen(argv[1], "rb");
    if (!fpi) { return fprintf(stderr, "error: cannot open file `%s`\n", argv[1]), EXIT_FAILURE; }

    // Read & process video frames
    size_t i = 0;
    size_t nb_bytes = 1;
    while ((nb_bytes = fread(frames[i], sizeof(uint8_t), HEIGHT * WIDTH * 3, fpi))) {
        grayscale_weighted(frames[i]);
        i += 1;
    }

    float64_t samples[MAX_SAMPLES];
#pragma omp parallel for
    for (size_t i = 0; i < MAX_SAMPLES; ++i) {
        struct timespec t1, t2;
        float64_t elapsed_ms = 0.0;
        do {
            clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
            sobel_baseline(frames[i], frames[i], 100.0F * 100.0F);
            clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
            elapsed_ms =
                (float64_t)(t2.tv_sec - t1.tv_sec) + (float64_t)(t2.tv_nsec - t1.tv_nsec) * 1.0E-6;
        } while (elapsed_ms <= 0.0);
        if (i < MAX_SAMPLES) { samples[i] = elapsed_ms; }
    }

    FILE* fpo = fopen(argv[2], "wb");
    if (!fpo) { return fprintf(stderr, "error: cannot open file `%s`\n", argv[2]), EXIT_FAILURE; }
    for (size_t i = 0; i < MAX_SAMPLES; ++i) {
        // Write this frame to the output pipe
        fwrite(frames[i], sizeof(uint8_t), HEIGHT * WIDTH * 3, fpo);
    }

    sort(samples, MAX_SAMPLES);
    float64_t min = samples[0];
    float64_t max = samples[MAX_SAMPLES - 1];
    float64_t med = samples[(MAX_SAMPLES + 1) / 2];
    float64_t avg = mean(samples, MAX_SAMPLES);
    float64_t dev = sdev(samples, MAX_SAMPLES, avg);

    fprintf(
        stderr,
        "%12s; %12s; %12s; %12s; %12s; %12s; %12s;\n",
        "Size (MiB)",
        "Minimum (ms)",
        "Median (ms)",
        "Average (ms)",
        "Maximum (ms)",
        "Bandwidth (MiB/s)",
        "Standard deviation (%)"
    );
    fprintf(
        stderr,
        "%12.3lf; %12.3lf; %12.3lf; %12.3lf; %12.3lf; %17.3lf; %22.3lf;\n",
        (float64_t)(size * 2) / (1024.0 * 1024.0),
        min,
        med,
        avg,
        max,
        (float64_t)((size * 2) / (1024.0 * 1024.0)) / (avg * 1.0E-3),
        (dev * 100.0 / avg)
    );

    fclose(fpi);
    fclose(fpo);
    for (size_t i = 0; i < MAX_SAMPLES; ++i) {
        free(frames[i]);
    }
    free(frames);

    return 0;
}
