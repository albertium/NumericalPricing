//
// Created by Albert Wong on 9/4/20.
//

#include "numerical.h"


double numerical::norm_cdf(double x) {
    return 0.5 * (1 + erf(x / M_SQRT2));
}

double numerical::norm_pdf(double x) {
    return exp(-x * x / 2) / sqrt(2 * M_PI);
}
