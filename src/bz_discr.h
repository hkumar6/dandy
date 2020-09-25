#include <stdlib.h>
#include <math.h>
#include "dbl_compare.h"

// extern int comparedim;
extern double globaldiscr;

double fmax(double a,double b);

// int cmpkeyk(double **pt1, double **pt2);
// int cmpkeyk(const void *pt1, const void *pt2);
// int dbl_compare(const void *a, const void *b);

int intpoints(double **pointset, int dim, int npoints, double *base);

double poly_discr(double **pointset, int dim, int npoints);
