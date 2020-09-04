//
// Created by Albert Wong on 9/4/20.
//

#ifndef HW1_COMMON_H
#define HW1_COMMON_H

#include "base.h"


namespace core {
    // Payoffs
    class CallPayoff: public Payoff {
    public:
        explicit CallPayoff(const Params &params) : Payoff(params) {}

        ArrayXd operator()(ArrayXd s) override {
            return (s - params_.k).max(0);
        }
    };

    class PutPayoff : public Payoff {
    public:
        explicit PutPayoff(const Params &params) : Payoff(params) {}

        ArrayXd operator()(ArrayXd s) override {
            return (params_.k - s).max(0);
        }
    };

    // Stepbacks
    class EuropeanStep : public Stepback {
    public:
        explicit EuropeanStep(const Params &params) : Stepback(params) {}

        ArrayXd operator()(ArrayXd values, ArrayXd s, Payoff intrinsic_func) override {
            return values;
        }
    };

    class AmericanStep : public Stepback {
    public:
        explicit AmericanStep(const Params &params) : Stepback(params) {}

        ArrayXd operator()(ArrayXd values, ArrayXd s, Payoff intrinsic_func) override {
            return values.max(intrinsic_func(s));
        }
    };
}

#endif //HW1_COMMON_H
