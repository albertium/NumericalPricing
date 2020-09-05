//
// Created by Albert Wong on 9/3/20.
//

#ifndef HW1_BINOMIALPRICER_H
#define HW1_BINOMIALPRICER_H

#include <type_traits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <Eigen/Dense>

#include "base.h"
#include "common.h"

using namespace Eigen;


namespace core {

    struct TreeTag {
        int n;

        friend std::ostream &operator<<(std::ostream &os, const TreeTag &tag) {
            os << tag.n;
            return os;
        }
    };

    template<typename PayoffT, typename AdjustT, typename StepbackT>
    class BinomialPricer : public Pricer<PayoffT, AdjustT, StepbackT, TreeTag> {
        using Pricer<PayoffT, AdjustT, StepbackT, TreeTag>::params_;
        using Pricer<PayoffT, AdjustT, StepbackT, TreeTag>::UNDEFINED;
        using Pricer<PayoffT, AdjustT, StepbackT, TreeTag>::payoff_;
        using Pricer<PayoffT, AdjustT, StepbackT, TreeTag>::adjust_;
        using Pricer<PayoffT, AdjustT, StepbackT, TreeTag>::stepback_;

    public:
        explicit BinomialPricer(const Params &params) : Pricer<PayoffT, AdjustT, StepbackT, TreeTag>(params) {}

        PricingOutput<TreeTag> price(const TreeTag &tag) override;

        void profile(const std::vector<int> &ns);
    };

    template<typename PayoffT, typename AdjustT, typename StepbackT>
    class BinomialAveragingPricer : public Pricer<PayoffT, AdjustT, StepbackT, TreeTag> {
        using Pricer<PayoffT, AdjustT, StepbackT, TreeTag>::params_;

    public:
        explicit BinomialAveragingPricer(const Params &params) : Pricer<PayoffT, AdjustT, StepbackT, TreeTag>(params) {}

        PricingOutput<TreeTag> price(const TreeTag &tag) override {
            BinomialPricer<PayoffT, AdjustT, StepbackT> pricer{params_};
            return pricer.price(tag) + pricer.price({tag.n + 1});
        }
    };

    template<typename PayoffT, typename AdjustT, typename StepbackT>
    class BinomialBSPricer : public Pricer<PayoffT, AdjustT, StepbackT, TreeTag> {
    public:
        explicit BinomialBSPricer(const Params &params) : Pricer<PayoffT, AdjustT, StepbackT, TreeTag>(params) {
            static_assert(std::is_same<CallPayoff, PayoffT>::value || std::is_same<PutPayoff, PayoffT>::value,
                          "BinomialBSPricer only supports Call or Put payoff.");
        }

        PricingOutput<TreeTag> price(const TreeTag &tag) override {
            return PricingOutput<TreeTag>();
        }
    };

}

#endif //HW1_BINOMIALPRICER_H
