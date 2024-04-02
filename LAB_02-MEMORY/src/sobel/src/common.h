#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef float  float32_t;
typedef double float64_t;

// Resolution
#define WIDTH 1280
#define HEIGHT 720
#define MAX_SAMPLES 360

#define idx2d(row, col, n) (((row) * (n)) + (col))

// Sorts an array of double-precision floating-point elements.
void sort(float64_t* restrict array, size_t len);

// Computes the arithmetic mean of an array of double-precision floating-point elements.
float64_t mean(float64_t const* restrict array, size_t len);

// Computes the standard deviation of an array of double-precision floating-point elements.
float64_t sdev(float64_t const* restrict array, size_t len, float64_t mean);
