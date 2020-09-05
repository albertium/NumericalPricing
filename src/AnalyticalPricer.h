//
// Created by Albert Wong on 9/4/20.
//

#ifndef HW1_ANALYTICALPRICER_H
#define HW1_ANALYTICALPRICER_H

#include <type_traits>

#include "base.h"
#include "common.h"
#include "numerical.h"


namespace core {
    template <typename PayoffT, typename StepbackT>
    class AnalyticalPricer : Pricer<PayoffT, PayoffT, StepbackT> {
        using Pricer<PayoffT, PayoffT, StepbackT>::params_;

    public:
        explicit AnalyticalPricer(const Params &params) : Pricer<PayoffT, PayoffT, StepbackT>(params) {
            // Sanity check
            static_assert(std::is_same<EuropeanStep, StepbackT>::value,
                    "Analytical pricer only supports European options");

            static_assert(
                    std::is_same<CallPayoff, PayoffT>::value || std::is_same<PutPayoff, PayoffT>::value,
                    "Analytical pricer only supports vanilla call and put");
        }

        PricingOutput<EmptyTag> price(const EmptyTag& tag) override;
    };
}



#endif //HW1_ANALYTICALPRICER_H
