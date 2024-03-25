/**
 * \file mkekin.c
 **/

/**
 * \brief Scale forces, update velocities and compute K.E.
 **/
double mkekin(int npart, double f[], double vh[], double hsq2, double hsq) {
    double sum = 0.0, ekin;

    for (int i = 0; i < 3 * npart; i++) {
        f[i] *= hsq2;
        vh[i] += f[i];
        sum += vh[i] * vh[i];
    }
    ekin = sum / hsq;

    return ekin;
}
