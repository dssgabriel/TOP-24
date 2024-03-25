/**
 * \file velavg.c
 **/

#include <math.h>

/**
 * \brief Compute average velocity.
 **/
double velavg(int npart, double vh[], double vaver, double h) {
    double vaverh = vaver * h;
    double vel = 0.0;
    double sq;
    extern double count;

    count = 0.0;
    for (int i = 0; i < npart * 3; i += 3) {
        sq = sqrt(vh[i] * vh[i] + vh[i + 1] * vh[i + 1] + vh[i + 2] * vh[i + 2]);
        if (sq > vaverh) count++;
        vel += sq;
    }
    vel /= h;

    return (vel);
}
