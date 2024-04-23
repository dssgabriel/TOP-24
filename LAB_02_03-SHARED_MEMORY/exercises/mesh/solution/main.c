#include <omp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NSTEPS 1000

/* Exercise 3 : AoS vs SoA */
typedef struct mesh_s {
  double *acceleration;
  double *velocity;
  uint16_t *x;
  uint16_t *y;
  uint16_t nx;
  uint16_t ny;
} mesh_t;

mesh_t mesh_new(uint16_t nx, uint16_t ny) {
  size_t size = nx * ny;

  double *acceleration = malloc(sizeof(double) * size);
  double *velocity = malloc(sizeof(double) * size);
  uint16_t *x = malloc(sizeof(uint16_t) * size);
  uint16_t *y = malloc(sizeof(uint16_t) * size);

  return (mesh_t){
      .acceleration = acceleration,
      .velocity = velocity,
      .x = x,
      .y = y,
      .nx = nx,
      .ny = ny,
  };
}

void mesh_drop(mesh_t mesh[static 1]) {
  free(mesh->acceleration);
  free(mesh->velocity);
  free(mesh->x);
  free(mesh->y);
}

/* Exercise 3 : AoS vs SoA */
void mesh_compute_velocity(mesh_t mesh[static 1], int nthreads) {
#pragma omp parallel num_threads(nthreads)
  {
#pragma omp for
    for (size_t i = 0; i < mesh->nx; ++i) {
      mesh->acceleration[i] = 0.0;
      // for (size_t j = 0; j < mesh->ny; ++j) {
      //     if (i != j) {
      //         mesh->acceleration[i] += 0.1337 * (mesh->x[j] - mesh->x[i]) +
      //         (mesh->y[j] - mesh->y[i]);
      //     }
      // }
      for (size_t j = 0; j < i; ++j) {
        mesh->acceleration[i] +=
            0.1337 * (mesh->x[j] - mesh->x[i]) + (mesh->y[j] - mesh->y[i]);
      }
      for (size_t j = i + 1; j < mesh->ny; ++j) {
        mesh->acceleration[i] +=
            0.1337 * (mesh->x[j] - mesh->x[i]) + (mesh->y[j] - mesh->y[i]);
      }
    }

#pragma omp for
    for (size_t c = 0; c < mesh->nx * mesh->ny; ++c) {
      mesh->velocity[c] += mesh->acceleration[c];
    }
  }
}

double elapsed_s(struct timespec t0, struct timespec t1) {
  return (double)(t1.tv_sec - t0.tv_sec) +
         (double)(t1.tv_nsec - t0.tv_nsec) / 1.0e9;
}

int main(int argc, char *argv[argc + 1]) {
      if (argc < 4) {
        fprintf(stderr, "Usage: %s <NCELLS_X> <NCELLS_Y> <NTHREADS>\n", argv[0]);
        return -1;
    }

    uint16_t nx = (uint16_t)atoi(argv[1]);
    uint16_t ny = (uint16_t)atoi(argv[2]);
    int nthreads = atoi(argv[3]);

    mesh_t mesh = mesh_new(nx, ny);
    // mesh_init(&mesh);

    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC_RAW, &t0);
    for (size_t it = 0; it < NSTEPS; ++it) {
        mesh_compute_velocity(&mesh, nthreads);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
    printf("%d %.9lf\n", nthreads, elapsed_s(t0, t1));

    mesh_drop(&mesh);
    return 0;
}
