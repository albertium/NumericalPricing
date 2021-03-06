//
// Created by Albert Wong on 9/4/20.
//

#include "numerical.h"


double numerical::norm_cdf(const double &x) {
    return 0.5 * (1 + erf(x / M_SQRT2));
}

double numerical::norm_pdf(const double &x) {
    return exp(-x * x / 2) / sqrt(2 * M_PI);
}

ArrayXd numerical::norm_cdf(const ArrayXd &x) {
    return ((x / M_SQRT2).erf() + 1) * 0.5;
}

ArrayXd numerical::norm_pdf(const ArrayXd &x) {
    return (-x.square() / 2 / sqrt(2 * M_PI)).exp();
}
