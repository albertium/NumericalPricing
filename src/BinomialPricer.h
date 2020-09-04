//
// Created by Albert Wong on 9/3/20.
//

#ifndef HW1_BINOMIALPRICER_H
#define HW1_BINOMIALPRICER_H

#include <cmath>
#include <iostream>
#include <vector>
#include <Eigen/Dense>

#include "base.h"

using namespace Eigen;


namespace core {

    struct TreeTag {
        int n;

        friend std::ostream &operator<<(std::ostream &os, const TreeTag &tag) {
            os << tag.n;
            return os;
        }
    };

    template <typename PayoffT, typename IntrinsicT, typename StepbackT>
    class BinomialPricer : public Pricer<PayoffT, IntrinsicT, StepbackT, TreeTag> {
        using Pricer<PayoffT, IntrinsicT, StepbackT, TreeTag>::params_;
        using Pricer<PayoffT, IntrinsicT, StepbackT, TreeTag>::UNDEFINED;
        using Pricer<PayoffT, IntrinsicT, StepbackT, TreeTag>::payoff_;
        using Pricer<PayoffT, IntrinsicT, StepbackT, TreeTag>::intrinsic_;
        using Pricer<PayoffT, IntrinsicT, StepbackT, TreeTag>::stepback_;

    public:
        explicit BinomialPricer(const Params &params) : Pricer<PayoffT, IntrinsicT, StepbackT, TreeTag>(params) {}

        PricingOutput<TreeTag> price(TreeTag tag) override;
    };



}


#endif //HW1_BINOMIALPRICER_H
