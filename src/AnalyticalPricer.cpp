//
// Created by Albert Wong on 9/4/20.
//

#include "AnalyticalPricer.h"

using namespace numerical;


namespace core {
    template<typename PayoffT, typename StepbackT>
    PricingOutput<EmptyTag> AnalyticalPricer<PayoffT, StepbackT>::price(const EmptyTag& tag) {
        double s = params_.s, k = params_.k, r = params_.r, q = params_.q, sig = params_.sig, t = params_.t;
        double total_vol = sig * sqrt(t);
        double d1 = (log(s / k) + (r - q) * t) / total_vol + 0.5 * total_vol;
        double d2 = d1 - total_vol;
        double q_fac = exp(-q * t), r_fac = exp(-r * t);
        double c_d1 = norm_cdf(d1), c_d2 = norm_cdf(d2);

        double value, delta, gamma, theta;
        gamma = q_fac * norm_pdf(d1) / s / total_vol;

        if (std::is_same<CallPayoff, PayoffT>::value) {
            value = s * q_fac * c_d1 - k * r_fac * c_d2;
            delta = q_fac * c_d1;
            theta = -q_fac * s * norm_pdf(d1) * sig / 2 / sqrt(t) - r * k * r_fac * c_d2 + q * s * q_fac * c_d1;
        } else {
            value = k * r_fac * (1 - c_d2) - s * q_fac * (1 - c_d1);
            delta = -q_fac * (1 - c_d1);
            theta = -q_fac * s * norm_pdf(-d1) * sig / 2 / sqrt(t) + r * k * r_fac * (1 - c_d2) - q * s * q_fac * (1 - c_d1);
        }

        return {tag, value, delta, gamma, theta};
    }
}