//
// Created by Albert Wong on 9/3/20.
//

#include "BinomialPricer.h"
#include <fstream>


template<typename PayoffT, typename AdjustT, typename StepbackT>
core::PricingOutput<core::TreeTag> core::BinomialPricer<PayoffT, AdjustT, StepbackT>::price(const core::TreeTag& tag) {
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
    std::vector<ArrayXd> value_grid{payoff_(spot_grid.back())};
    for (int i = (int)spot_grid.size() - 2; i >= 0; --i) {
        const ArrayXd& last = value_grid.back();
        ArrayXd values = stepback_(
                disc * (p * last.segment(0, i + 1) + (1 - p) * last.segment(1, i + 1)),
                spot_grid[i],
                adjust_
        );
        value_grid.emplace_back(std::move(values));
    }

    // Calculate metrics
    const ArrayXd& v1 = value_grid[n - 1], v2 = value_grid[n - 2];
    const ArrayXd& s1 = spot_grid[1], s2 = spot_grid[2];
    double value = value_grid.back()[0];
    double delta = (v1(0) - v1(1)) / (s1(0) - s1(1));
    double delta21 = (v2(0) - v2(1)) / (s2(0) - s2(1));
    double delta22 = (v2(1) - v2(2)) / (s2(1) - s2(2));
    double gamma = (delta21 - delta22) / (s2(0) - s2(2)) * 2;
    double theta = (v2(1) - value) / 2 / dt;

    return {tag, value, delta, gamma, theta};
}

template<typename PayoffT, typename IntrinsicT, typename StepbackT>
void core::BinomialPricer<PayoffT, IntrinsicT, StepbackT>::profile(const std::vector<int>& ns) {
//    std::ofstream file{"/Users/wonalbe/CLionProjects/NumericalPricing/output/hw1.csv"};
    std::ofstream file{"../output/hw1.csv"};
    for (const int& n: ns)
        file << price({n}) << std::endl;
}
