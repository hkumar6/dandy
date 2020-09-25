#include <R.h>
#include <Rinternals.h>

#include <cstdio>
#include <cstdlib>
#include <algorithm>

#include "dem_discr.h"
#include "TA_shrink_delta.h"
#include "TA_shrink_bardelta.h"
#include "discrepancy.h"
#include "macros.h"

/*
 * EXACT STAR-DISCREPANCY ALGORITHM
 * @note: Running time is O(n^{1 + d/2})
 *
 * @param r_points [(d x n) matrix] Matrix of points.
 *
 * @return [numeric(1)] Star discrepancy.
 */
// [[Rcpp::export]]
SEXP discrepancyExact(SEXP r_points) {
  // first unpack R structures
  EXTRACT_NUMERIC_MATRIX(r_points, c_points, dim, n_points);
  
  double **pointset, upper, lower;
  
  // ugly way to convert SEXP to double array
  pointset = (double **)malloc(n_points * sizeof(double*));
  for (int i = 0; i < n_points; i++) {
    pointset[i] = (double *)malloc(dim * sizeof(double));
    
    // get start
    double *start = c_points + i * dim;
    
    for (int j = 0; j < dim; j++) {
      // newline counts as whitespace
      pointset[i][j] = start[j];
    }
  }
  
  upper = oydiscr(pointset, dim, n_points, &lower);
  
  return ScalarReal(upper);
}

/*
 * THRESHOLD ACCEPTING ALGORITHM BY GNEWUCH, WAHLSTROEM AND WINZEN
 * (https://epubs.siam.org/doi/10.1137/110833865)
 *
 * @param r_points [(d x n) matrix] Matrix of points.
 * @param r_iteer [integer(1)] Number of iterations per trial.
 * @param r_max_trials [integer(1)] Maximum number of trials.
 *
 * @return [numeric(1)] Estimate for star discrepancy.
 */
// [[Rcpp::export]]
SEXP discrepancyGWW(SEXP r_points, SEXP r_iter, SEXP r_max_trials) {
  // first unpack R structures
  EXTRACT_NUMERIC_MATRIX(r_points, c_points, dim, n_points);
  EXTRACT_INTEGER(r_iter, iter);
  EXTRACT_INTEGER(r_max_trials, max_trials);
  
  double **pointset, delta_result, bardelta_result;
  
  // ugly way to convert SEXP to double array
  pointset = (double **)malloc(n_points * sizeof(double*));
  for (int i = 0; i < n_points; i++) {
    pointset[i] = (double *)malloc(dim * sizeof(double));
    
    // get start
    double *start = c_points + i * dim;
    
    for (int j = 0; j < dim; j++) {
      // newline counts as whitespace
      pointset[i][j] = start[j];
    }
  }
  
  delta_result = delta_calc(pointset, n_points, dim, iter, max_trials);
  bardelta_result = bardelta_calc(pointset, n_points, dim, iter, max_trials);
  
  // return maximum of both estimates
  return ScalarReal(std::max(delta_result, bardelta_result));
}
