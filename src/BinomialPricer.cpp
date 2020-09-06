//
// Created by Albert Wong on 9/3/20.
//

#include "BinomialPricer.h"

namespace core {
    // ========== Vanilla Binomial Pricing ==========
    template<typename PayoffT, typename AdjustT, typename StepbackT>
    PricingOutput<TreeTag>
    BinomialPricer<PayoffT, AdjustT, StepbackT>::price(const TreeTag &tag) {
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
        for (int i = (int) spot_grid.size() - 2; i >= 0; --i) {
            const ArrayXd &last = value_grid.back();
            ArrayXd values = stepback_(
                    disc * (p * last.segment(0, i + 1) + (1 - p) * last.segment(1, i + 1)),
                    spot_grid[i],
                    adjust_
            );
            value_grid.emplace_back(std::move(values));
        }

        // Calculate metrics
        const ArrayXd &v1 = value_grid[n - 1], v2 = value_grid[n - 2];
        const ArrayXd &s1 = spot_grid[1], s2 = spot_grid[2];
        double value = value_grid.back()[0];
        double delta = (v1(0) - v1(1)) / (s1(0) - s1(1));
        double delta21 = (v2(0) - v2(1)) / (s2(0) - s2(1));
        double delta22 = (v2(1) - v2(2)) / (s2(1) - s2(2));
        double gamma = (delta21 - delta22) / (s2(0) - s2(2)) * 2;
        double theta = (v2(1) - value) / 2 / dt;

        return {tag, value, delta, gamma, theta};
    }

    // ========== Binomial pricing with Black Scholes ==========
    template<typename PayoffT, typename AdjustT, typename StepbackT>
    PricingOutput<TreeTag> BinomialBSPricer<PayoffT, AdjustT, StepbackT>::price(const TreeTag &tag) {
        // Set up parameters
        int n = tag.n;
        double s = params_.s, k = params_.k, t = params_.t, r = params_.r, q = params_.q, sig = params_.sig;
        double dt = t / n;
        double disc = exp(-r * dt);
        double u = exp(sig * sqrt(dt));
        double d = 1 / u;
        double p = (exp((r - q) * dt) - d) / (u - d);

        // Set up grids
        std::vector<ArrayXd> spot_grid{ArrayXd{1}};
        spot_grid.back() << s;
        for (int i = 1; i < n; ++i) {  // only need to populate up to n - 1
            ArrayXd curr{i + 1};
            curr.segment(0, i) = spot_grid.back() * u;
            curr.tail(1) = spot_grid.back().tail(1) * d;
            spot_grid.push_back(std::move(curr));
        }

        // Apply Black Scholes payoff
        double total_vol = sig * sqrt(dt);
        ArrayXd d1 = ((spot_grid.back() / k).log() + (r - q) * dt) / total_vol + 0.5 * total_vol;
        ArrayXd d2 = d1 - total_vol;
        ArrayXd bs_payoff;
        if (std::is_same<CallPayoff, PayoffT>::value)
            bs_payoff = spot_grid.back() * norm_cdf(d1) * exp(-q * dt) - k * norm_cdf(d2) * exp(-r * dt);
        else
            bs_payoff = k * norm_cdf(-d2) * exp(-r * dt) - spot_grid.back() * norm_cdf(-d1) * exp(-q * dt);

        // Step back
        std::vector<ArrayXd> value_grid{std::move(bs_payoff)};
        for (int i = (int) spot_grid.size() - 2; i >= 0; --i) {
            const ArrayXd &last = value_grid.back();
            ArrayXd values = stepback_(
                    disc * (p * last.segment(0, i + 1) + (1 - p) * last.segment(1, i + 1)),
                    spot_grid[i],
                    adjust_
            );
            value_grid.emplace_back(std::move(values));
        }

        // Calculate metrics
        const ArrayXd &v1 = value_grid[n - 2], v2 = value_grid[n - 3];
        const ArrayXd &s1 = spot_grid[1], s2 = spot_grid[2];
        double value = value_grid.back()[0];
        double delta = (v1(0) - v1(1)) / (s1(0) - s1(1));
        double delta21 = (v2(0) - v2(1)) / (s2(0) - s2(1));
        double delta22 = (v2(1) - v2(2)) / (s2(1) - s2(2));
        double gamma = (delta21 - delta22) / (s2(0) - s2(2)) * 2;
        double theta = (v2(1) - value) / 2 / dt;

        return {tag, value, delta, gamma, theta};
    }
}