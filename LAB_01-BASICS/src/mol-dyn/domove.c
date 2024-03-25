/**
 * \file domove.c
 **/

/**
 * \brief Move particles.
 **/
void domove(int n3, double x[], double vh[], double f[], double side) {
    for (int i = 0; i < n3; i++) {
        x[i] += vh[i] + f[i];

        // Periodic boundary conditions
        if (x[i] < 0.0) { x[i] += side; }
        if (x[i] > side) { x[i] -= side; }

        // Partial velocity updates
        vh[i] += f[i];
        // Initialise forces for the next iteration
        f[i] = 0.0;
    }
}
