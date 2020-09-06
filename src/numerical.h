//
// Created by Albert Wong on 9/4/20.
//

#ifndef HW1_NUMERICAL_H
#define HW1_NUMERICAL_H

#include <cmath>
#include <Eigen/Dense>
#include <unsupported/Eigen/SpecialFunctions>

using namespace Eigen;


namespace numerical {
    // Scalar functions
    double norm_cdf(const double &x);  // Normal distribution CDF
    double norm_pdf(const double &x);  // Normal distribution PDF

    // Vectorized functions
    ArrayXd norm_cdf(const ArrayXd &x);

    ArrayXd norm_pdf(const ArrayXd &x);
}

#endif //HW1_NUMERICAL_H
