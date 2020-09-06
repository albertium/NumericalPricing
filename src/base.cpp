//
// Created by Albert Wong on 9/5/20.
//
#include "base.h"


namespace core {
    template<typename TagT>
    PricingOutput<TagT> PricingOutput<TagT>::operator+(const PricingOutput<TagT> &other) {
        return {tag, price + other.price, delta + other.delta, gamma + other.gamma, theta + other.theta};
    }

    template<typename TagT>
    PricingOutput<TagT> PricingOutput<TagT>::operator-(const PricingOutput<TagT> &other) {
        return {tag, price - other.price, delta - other.delta, gamma - other.gamma, theta - other.theta};
    }

    template<typename TagT>
    PricingOutput<TagT> PricingOutput<TagT>::operator*(const double &scalar) {
        return {tag, price * scalar, delta * scalar, gamma * scalar, theta * scalar};
    }

    template<typename TagT>
    PricingOutput<TagT> PricingOutput<TagT>::operator/(const double &scalar) {
        return {tag, price / scalar, delta / scalar, gamma / scalar, theta / scalar};
    }

    template<typename PayoffT, typename AdjustT, typename StepbackT, typename TagT>
    Pricer<PayoffT, AdjustT, StepbackT, TagT>::Pricer(const Params &params)
            :Parameterizable(params), payoff_(params), adjust_(std::make_unique<AdjustT>(params)), stepback_(params) {
        static_assert(std::is_base_of<Payoff, PayoffT>::value, "PayoffT must be subclass of Payoff");
        static_assert(std::is_base_of<Payoff, AdjustT>::value, "AdjustT must be subclass of Payoff");
        static_assert(std::is_base_of<Stepback, StepbackT>::value, "StepbackT must be subclass of Stepback");
        static_assert(std::is_base_of<Tag, TagT>::value, "TagT must be subclass of Tag");
    }

    template<typename PayoffT, typename AdjustT, typename StepbackT, typename TagT>
    void Pricer<PayoffT, AdjustT, StepbackT, TagT>::profile(const std::vector<TagT> &tags, const std::string &name) {
        std::ofstream file{"../output/" + name + ".csv"};
        file << tags[0].header() << ",Price,Delta,Gamma,Theta" << std::endl;
        for (const TagT &tag : tags)
            file << price(tag) << std::endl;
    }
}