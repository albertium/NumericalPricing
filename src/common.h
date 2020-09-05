//
// Created by Albert Wong on 9/4/20.
//

#ifndef HW1_COMMON_H
#define HW1_COMMON_H

#include "base.h"
#include "numerical.h"

using namespace numerical;


namespace core {
    // Payoffs
    class CallPayoff: public Payoff {
    public:
        explicit CallPayoff(const Params &params) : Payoff(params) {}

        ArrayXd operator()(const ArrayXd& s) override {
            return (s - params_.k).max(0);
        }
    };

    class PutPayoff : public Payoff {
    public:
        explicit PutPayoff(const Params &params) : Payoff(params) {}

        ArrayXd operator()(const ArrayXd& s) override {
            return (params_.k - s).max(0);
        }
    };

    class CallBSPayoff : public Payoff {
    public:
        explicit CallBSPayoff(const Params &params) : Payoff(params) {}

        ArrayXd operator()(const ArrayXd &s) override {
            double k = params_.k, r = params_.r, q = params_.q, sig = params_.sig, t = params_.t;
            double total_vol = sig * sqrt(t);
            ArrayXd d1 = ((s / k).log() + (r - q) * t) / total_vol + 0.5 * total_vol;
            ArrayXd d2 = d1 - total_vol;
            return s * norm_cdf(d1) * exp(-q * t) - k * norm_cdf(d2) * exp(-r * t);
        }
    };

    class PutBSPayoff : public Payoff {
    public:
        explicit PutBSPayoff(const Params &params) : Payoff(params) {}

        ArrayXd operator()(const ArrayXd &s) override {
            double k = params_.k, r = params_.r, q = params_.q, sig = params_.sig, t = params_.t;
            double total_vol = sig * sqrt(t);
            ArrayXd d1 = ((s / k).log() + (r - q) * t) / total_vol + 0.5 * total_vol;
            ArrayXd d2 = d1 - total_vol;
            return k * norm_cdf(-d2) * exp(-r * t) - s * norm_cdf(-d1) * exp(-q * t);
        }
    };

    // Stepbacks
    class EuropeanStep : public Stepback {
    public:
        explicit EuropeanStep(const Params &params) : Stepback(params) {}

        ArrayXd operator()(const ArrayXd& values, const ArrayXd& s, std::shared_ptr<Payoff> adjust_func) override {
            return values;
        }
    };

    class AmericanStep : public Stepback {
    public:
        explicit AmericanStep(const Params &params) : Stepback(params) {}

        ArrayXd operator()(const ArrayXd& values, const ArrayXd& s, std::shared_ptr<Payoff> adjust_func) override {
            return values.max((*adjust_func)(s));
        }
    };
}

#endif //HW1_COMMON_H
