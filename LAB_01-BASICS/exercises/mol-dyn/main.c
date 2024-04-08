/**
 * \file main.c
 **/

#include <locale.h>
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <time.h>

#define MAXI

#ifdef MAXI
#    define mm 15
#elif MEDIUM
#    define mm 10
#elif MINI
#    define mm 7
#else
#    error "`NPART` is not correctly defined. To build: make NPART=<MINI|MEDIUM|MAXI>"
#endif
#define npart 4 * mm* mm* mm

// Function forward declarations
void dfill(int, double, double[], int);

void domove(int, double[], double[], double[], double);

void dscal(int, double, double[], int);

void fcc(double[], int, int, double);

void forces(int, double[], double[], double, double);

double mkekin(int, double[], double[], double, double);

void mxwell(double[], int, double, double);

void prnout(int, double, double, double, double, double, double, int, double);

double velavg(int, double[], double, double);

time_t starttime = 0;
double secnds(void) {
    return omp_get_wtime();
}

// Variable declarations
double epot;
double vir;
double count;

// Main program : Molecular Dynamics simulation.
int main(void) {
    int move;
    double x[npart * 3], vh[npart * 3], f[npart * 3];
    double ekin;
    double vel;
    double sc;
    double start, time;

    // Parameter definitions
    double den = 0.83134;
    double side = pow((double)npart / den, 0.3333333);
    double tref = 0.722;
    double rcoff = (double)mm / 4.0;
    double h = 0.064;
    int irep = 10;
    int istop = 20;
    int iprint = 5;
    int movemx = 20;

    double a = side / (double)mm;
    double hsq = h * h;
    double hsq2 = hsq * 0.5;
    double tscale = 16.0 / ((double)npart - 1.0);
    double vaver = 1.13 * sqrt(tref / 24.0);

    // Initial output
    setlocale(LC_ALL, "");
    puts("*******************************************************");
    puts("           M1 CHPS - TOP LAB_01: MD SIM\n");
    puts("   Molecular Dynamics Simulation example program");
    puts("-------------------------------------------------------");
    printf(" # of particles .................... %6d\n", npart);
    printf(" box side length ................... %13.6f\n", side);
    printf(" cut off ........................... %13.6f\n", rcoff);
    printf(" reduced temperature ............... %13.6f\n", tref);
    printf(" basic timestep .................... %13.6f\n", h);
    printf(" temperature scale interval ........ %6d\n", irep);
    printf(" stop scaling at move .............. %6d\n", istop);
    printf(" print interval .................... %6d\n", iprint);
    printf(" total # of steps .................. %6d\n", movemx);
    puts("-------------------------------------------------------");

    // Generate fcc lattice for atoms inside box
    fcc(x, npart, mm, a);
    // Initialise velocities and forces (which are zero in fcc positions)
    mxwell(vh, 3 * npart, h, tref);
    dfill(3 * npart, 0.0, f, 1);
    // Start of md
    printf("\n    i       ke         pe            e         temp   "
           "   pres      vel      rp\n  -----  ----------  ----------"
           "  ----------  --------  --------  --------  ----\n");

    start = secnds();
    for (move = 1; move <= movemx; move++) {
        // Move the particles and partially update velocities
        domove(3 * npart, x, vh, f, side);

        // Compute forces in the new positions and accumulate the virial and potential energy.
        forces(npart, x, f, side, rcoff);

        // Scale forces, complete update of velocities and compute k.e.
        ekin = mkekin(npart, f, vh, hsq2, hsq);

        // Average the velocity and temperature scale if desired
        vel = velavg(npart, vh, vaver, h);
        if (move < istop && fmod(move, irep) == 0) {
            sc = sqrt(tref / (tscale * ekin));
            dscal(3 * npart, sc, vh, 1);
            ekin = tref / tscale;
        }

        // Sum to get full potential energy and virial
        if (fmod(move, iprint) == 0) {
            prnout(move, ekin, epot, tscale, vir, vel, count, npart, den);
        }
    }
    time = secnds() - start;

    printf("Time: %lf\n", time);
    puts("*******************************************************");
}
