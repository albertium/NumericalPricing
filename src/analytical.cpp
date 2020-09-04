//
// Created by Albert Wong on 9/2/20.
//
#include "analytical.h"

using namespace std;


double analytical::norm_cdf(double x) {
    return 0.5 * (1 + erf(x / M_SQRT2));
}

double analytical::norm_pdf(double x) {
    return exp(-x * x / 2) / sqrt(2 * M_PI);
}

double analytical::PriceBlackScholesCall(double s, double k, double r, double q, double sig, double t) {
    double total_vol = sig * sqrt(t);
    double d1 = (log(s / k) + (r - q) * t) / total_vol + 0.5 * total_vol;
    double d2 = d1 - total_vol;
    return s * exp(-q * t) * norm_cdf(d1) - k * exp(-r * t) * norm_cdf(d2);
}

double analytical::PriceBlackScholesPut(double s, double k, double r, double q, double sig, double t) {
    double forward_price = s * exp(-q * t) - k * exp(-r * t);
    return PriceBlackScholesCall(s, k, r, q, sig, t) - forward_price;
}
