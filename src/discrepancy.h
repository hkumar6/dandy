#include <R.h>
#include <Rinternals.h>

#include <stdio.h>
#include <stdlib.h>

#include "dem_discr.h"
#include "macros.h"
#include "TA_shrink_delta.h"
#include "TA_shrink_bardelta.h"

SEXP discrepancyExact(SEXP r_points);
SEXP discrepancyGWW(SEXP r_points, SEXP r_iter, SEXP r_max_trials);
