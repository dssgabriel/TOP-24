/*
  This program is a modified version of the N queens program found in the Barcelona OpenMP Tasks
  Suite. Copyright since 2016 the OMPi Team Dept. of Computer Science & Engineering, University of
  Ioannina This program is free software; you can redistribute it and/or modify it under the terms
  of the GNU General Public License as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version. This program is distributed in the hope
  that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

/* Copyright statements located in the program found in the Barcelona OpenMP Tasks Suite:
 *
 *    This program is part of the Barcelona OpenMP Tasks Suite
 *    Copyright (C) 2009 Barcelona Supercomputing Center - Centro Nacional de Supercomputacion
 *    Copyright (C) 2009 Universitat Politecnica de Catalunya
 *
 *    Original code from the Cilk project (by Keith Randall)
 *    Copyright (c) 2000 Massachusetts Institute of Technology
 *    Copyright (c) 2000 Matteo Frigo
 */

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESULT_NA 0
#define RESULT_SUCCESSFUL 1
#define RESULT_UNSUCCESSFUL 2

#define MAX_SOLUTIONS sizeof(solutions) / sizeof(int)

#define MAX_QUEENS 14

/* Checking information */
void* memset(void* s, int c, size_t n);
void* memcpy(void* dest, void const* src, size_t n);

static int solutions[14] = {
    1,    0,     0,     2,      10,  /* 5 */
    4,    40,    92,    352,    724, /* 10 */
    2680, 14200, 73712, 365596,
};

/*
 * <a> contains array of <n> queen positions.  Returns 1
 * if none of the queens conflict, and returns 0 otherwise.
 */
int ok(int n, char* a) {
    int i, j;
    char p, q;

    for (i = 0; i < n; i++) {
        p = a[i];

        for (j = i + 1; j < n; j++) {
            q = a[j];
            if (q == p || q == p - (j - i) || q == p + (j - i)) { return 0; }
        }
    }

    return 1;
}

int nqueens_ser(int n, int j, char* a) {
    int i;
    int solutions;

    if (n == j) {
        // good solution, count it
        solutions = 1;
        return solutions;
    }

    solutions = 0;

    // try each possible position for queen <j>
    for (i = 0; i < n; i++) {
        {
            // allocate a temporary array and copy <a> into it
            a[j] = (char)i;
            if (ok(j + 1, a)) { solutions += nqueens_ser(n, j + 1, a); }
        }
    }

    return solutions;
}

int find_queens(int size) {
    int total_count = 0;
    double t1, t2;

    t1 = omp_get_wtime();
    {
        char a[MAX_QUEENS];
        total_count = nqueens_ser(size, 0, a);
    }
    t2 = omp_get_wtime();

    printf("Found %d, Time = %f\n", total_count, t2 - t1);
    return total_count;
}

int verify_queens(int size, int total_count) {
    if (size > MAX_SOLUTIONS) return RESULT_NA;
    if (total_count == solutions[size - 1]) return RESULT_SUCCESSFUL;
    return RESULT_UNSUCCESSFUL;
}

int main(int argc, char** argv) {
    int queens;
    int res;
    int total_count;

    if (argc < 2) {
        queens = 10;
        printf("No #queens given; using default number (%d).\n", queens);
    } else {
        queens = atoi(argv[1]);
        if (queens <= 1 || queens >= 15) {
            queens = 10;
            printf(
                "The number of queens should be at least 2 and less than 15; using default number "
                "(%d).\n",
                queens
            );
        }
    }

    printf("Running Parallel NQueens (%d) \n", queens);

    total_count = find_queens(queens);

    res = verify_queens(queens, total_count);

    printf(
        "Completed Verification = %s\n",
        (res == RESULT_NA) ? "NA" : ((res == RESULT_SUCCESSFUL) ? "SUCCESSFUL" : "UNSUCCESSFUL")
    );

    return 0;
}
