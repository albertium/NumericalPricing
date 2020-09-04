//
// Created by Albert Wong on 9/2/20.
//

#ifndef MTH9821_ANALYTICAL_H
#define MTH9821_ANALYTICAL_H

#include <iostream>
#include <cmath>

namespace analytical {
    // Basic analytical functions
    double norm_cdf(double x);  // normal distribution cdf
    double norm_pdf(double x);  // normal distribution pdf

    // Black Scholes option pricing functions
    double PriceBlackScholesCall(double s, double k, double r, double q, double sig, double t);
    double PriceBlackScholesPut(double s, double k, double r, double q, double sig, double t);
}

//double norm_cdf(double x);

#endif //MTH9821_ANALYTICAL_H
