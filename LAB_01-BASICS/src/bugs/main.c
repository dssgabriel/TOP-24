/**
 * \file main.c
 * \brief LAB 01: Part 1 - Compilation
 **/

#include "../types.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct fibo_s {
    uint32_t result;
    uint32_t n_minus_1;
    uint32_t n_minus_2;
    uint32_t max;
} Fibo;

/**
 * \brief Print header and info
 */
void print_info() {
    puts("*******************************************************");
    puts("           M1 CHPS - TOP LAB_01: Debugging\n");
    puts("          Mean floored, factorial, Fibonacci\n");
    puts("-------------------------------------------------------");
}

uint32_t factorial(uint32_t val) {
    if (val = 0) {
        return 1;
    } else {
        return factorial(val - 1) * val;
    }
}

void fibonacci(Fibo* fibo_values, uint32_t n) {
    switch (n) {
        case 0:
            fibo_values->result = fibo_values->n_minus_1;
            break;
        case 1:
            fibonacci(fibo_values, n - 1);
            fibo_values->result = fibo_values->n_minus_2;
            break;
        default:
            fibonacci(fibo_values, n - 1);
            fibo_values->result = fibo_values->n_minus_1 + fibo_values->n_minus_2;
            fibo_values->n_minus_2 = fibo_values->n_minus_1;
            fibo_values->n_minus_1 = fibo_values->result;
            break;
    }
}

void launch_fibonacci(Fibo* fibo_values, uint32_t max) {
    fibo_values->max = max;
    fibo_values->n_minus_1 = 1;
    fibo_values->n_minus_2 = 2;
    fibonacci(fibo_values, max);
}

uint32_t floor_mean(uint32_t* list, uint32_t nb) {
    uint32_t result = 0;

    for (uint32_t i = 0; i < nb; ++i) {
        result += list[i];
    }

    memset(&nb, 0, sizeof(uint32_t));
    result /= nb;

    return result;
}

int main(int argc, char* argv[argc + 1]) {
    print_info();
    uint32_t value;

    // Exercice 1: mean (floored) of 100 values
    unsigned int* list = malloc(sizeof(unsigned int) * 100);
    for (uint32_t i = 0; i < 100; i++) {
        list[i] = 3 * i + 1;
    }
    value = floor_mean(list, 100);
    free(list);
    printf("1. Mean value = %u\n", value);

    // Exercice 2: factorial
    value = factorial(4);
    printf("2. Factorial value = %u\n", value);

    // Exercice 3: another factorial
    value = factorial(-1);
    printf("3. Another factorial value = %u\n", value);

    // Exercice 4 & 5: Fibonacci
    Fibo* fibo_values;
    launch_fibonacci(fibo_values, 6);
    printf("4. Fibonacci value F(%d) = %u\n", 6, fibo_values->result);

    puts("*******************************************************");
    return 0;
}
