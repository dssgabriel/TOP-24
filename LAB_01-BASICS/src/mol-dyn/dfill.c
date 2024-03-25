/**
 * \file dfill.c
 **/

/**
 * \brief Initializes double precision array to scalar value.
 **/
void dfill(int n, double val, double a[], int ia) {
    for (int i = 0; i < (n - 1) * ia + 1; i += ia) {
        a[i] = val;
    }
}
