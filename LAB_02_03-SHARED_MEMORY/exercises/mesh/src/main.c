#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NSTEPS 1000

typedef enum cell_type_e {
    CELL_FLUID,
    CELL_BOUNDARY,
    CELL_GHOST,
    CELL_OBJECT,
    CELL_UNKNOWN,
} cell_type_t;

typedef struct cell_s {
    int32_t id;
    double velocity;
    char name_abrev;
    float pressure;
    bool is_ghost;
    uint16_t x;
    uint16_t y;
    double acceleration;
    cell_type_t kind;
} cell_t;

cell_t cell_new(int32_t id, char name_abrev, uint16_t max_x, uint16_t max_y) {
    cell_type_t kind;
    switch (name_abrev) {
        case 'f':
            kind = CELL_FLUID;
            break;
        case 'b':
            kind = CELL_BOUNDARY;
            break;
        case 'g':
            kind = CELL_GHOST;
            break;
        case 'o':
            kind = CELL_OBJECT;
            break;
        default:
            kind = CELL_UNKNOWN;
    }
    cell_t self = {
        .id = id,
        .velocity = drand48(),
        .name_abrev = name_abrev,
        .pressure = (float)drand48() * (float)(lrand48() % 1000000),
        .is_ghost = name_abrev == 'g' ? true : false,
        .x = (uint16_t)(lrand48() % max_x),
        .y = (uint16_t)(lrand48() % max_y),
        .acceleration = drand48(),
        .kind = kind,
    };
    return self;
}

typedef struct mesh_s {
    uint16_t nx;
    uint16_t ny;
    cell_t* cells;
} mesh_t;

mesh_t mesh_new(uint16_t nx, uint16_t ny) {
    size_t size = nx * ny;
    cell_t* cells = malloc(size * sizeof(cell_t));
    mesh_t mesh = {
        .nx = nx,
        .ny = ny,
        .cells = cells,
    };
    return mesh;
}

void mesh_drop(mesh_t* mesh) {
    free(mesh->cells);
}

void mesh_init(mesh_t* mesh) {
    for (int32_t c = 0; c < (int32_t)(mesh->nx * mesh->ny); ++c) {
        char rnd = (char)(lrand48() % 5);
        char kind;
        switch (rnd) {
            case 0:
                kind = 'f';
                break;
            case 1:
                kind = 'b';
                break;
            case 2:
                kind = 'g';
                break;
            case 3:
                kind = 'o';
                break;
            case 4:
                kind = 'u';
                break;
            default:
                __builtin_unreachable();
        }
        mesh->cells[c] = cell_new(c, kind, mesh->nx, mesh->ny);
    }
}

void mesh_compute_velocity(mesh_t* mesh) {
    for (size_t i = 0; i < mesh->nx; ++i) {
        mesh->cells[i].acceleration = 0;
        for (size_t j = 0; j < mesh->ny; ++j) {
            if (i != j) {
                mesh->cells[i].acceleration += 0.1337 * (mesh->cells[j].x - mesh->cells[i].x)
                                               + (mesh->cells[j].y - mesh->cells[i].y);
            }
        }
    }
    for (size_t c = 0; c < mesh->nx * mesh->ny; ++c) {
        mesh->cells[c].velocity += mesh->cells[c].acceleration;
    }
}

double elapsed(struct timespec t0, struct timespec t1) {
    return (double)(t1.tv_sec - t0.tv_sec) * 1.0e3 + (double)(t1.tv_nsec - t0.tv_nsec) * 1.0e-6;
}

int main(int argc, char* argv[argc + 1]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <NCELLS_X> <NCELLS_Y>\n", argv[0]);
        return -1;
    }

    uint16_t nx = (uint16_t)atoi(argv[1]);
    uint16_t ny = (uint16_t)atoi(argv[2]);
    mesh_t mesh = mesh_new(nx, ny);
    mesh_init(&mesh);

    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC_RAW, &t0);
    for (size_t it = 0; it < NSTEPS; ++it) {
        mesh_compute_velocity(&mesh);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
    printf("time: %.3lf ms\n", elapsed(t0, t1));

    mesh_drop(&mesh);
    return 0;
}
