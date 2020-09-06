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

        ArrayXd operator()(const ArrayXd &s) const override {
            return (s - params_.k).max(0);
        }
    };

    class PutPayoff : public Payoff {
    public:
        explicit PutPayoff(const Params &params) : Payoff(params) {}

        ArrayXd operator()(const ArrayXd &s) const override {
            return (params_.k - s).max(0);
        }
    };

    // Stepbacks
    class EuropeanStep : public Stepback {
    public:
        explicit EuropeanStep(const Params &params) : Stepback(params) {}

        ArrayXd operator()(const ArrayXd &values, const ArrayXd &s, const Payoff *adjust_func) const override {
            return values;
        }
    };

    class AmericanStep : public Stepback {
    public:
        explicit AmericanStep(const Params &params) : Stepback(params) {}

        ArrayXd operator()(const ArrayXd &values, const ArrayXd &s, const Payoff *adjust_func) const override {
            return values.max((*adjust_func)(s));
        }
    };
}

#endif //HW1_COMMON_H
