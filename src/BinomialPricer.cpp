//
// Created by Albert Wong on 9/3/20.
//

#include "BinomialPricer.h"
#include <fstream>


template<typename PayoffT, typename IntrinsicT, typename StepbackT>
core::PricingOutput<core::TreeTag> core::BinomialPricer<PayoffT, IntrinsicT, StepbackT>::price(core::TreeTag tag) {
    // Set up parameters
    int n = tag.n;
    double s = params_.s, t = params_.t, r = params_.r, q = params_.q, sig = params_.sig;
    double dt = t / n;
    double disc = exp(-r * dt);
    double u = exp(sig * sqrt(dt));
    double d = 1 / u;
    double p = (exp((r - q) * dt) - d) / (u - d);

    // Set up grids
    std::vector<ArrayXd> spot_grid{ArrayXd{1}};
    spot_grid.back() << s;
    for (int i = 1; i <= n; ++i) {
        ArrayXd curr{i + 1};
        curr.segment(0, i) = spot_grid.back() * u;
        curr.tail(1) = spot_grid.back().tail(1) * d;
        spot_grid.push_back(std::move(curr));
    }

    // Step back
    ArrayXd values = payoff_(spot_grid.back());
    for (int i = (int)spot_grid.size() - 2; i >= 0; --i) {
        values.segment(0, i + 1) = disc * (p * values.segment(0, i + 1) + (1 - p) * values.segment(1, i + 1));
    }

    return {tag, values(0), UNDEFINED, UNDEFINED, UNDEFINED};
}
