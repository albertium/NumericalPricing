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
    void Pricer<PayoffT, AdjustT, StepbackT, TagT>::profile(const std::vector<TagT> &tags,
                                                            const PricingOutput<> &exact, const std::string &name) {
        PricingOutput<TagT> benchmark{tags[0], exact.price, exact.delta, exact.gamma, exact.theta};
        std::ofstream file{"../output/" + name + ".csv"};
        file << tags[0].header()
             << ",Price,Delta,Gamma,Theta,Price Err,Delta Err,Gamma Err,Theta Err,1st Err,2nd Err" << std::endl;
        for (const TagT &tag : tags) {
            PricingOutput<TagT> out = price(tag);
            PricingOutput<TagT> err = abs(out - benchmark);
            PricingOutput<TagT> err_1st = err * tag.n, err_2nd = err * tag.n * tag.n;
            file << out << "," << err.price << "," << err.delta << "," << err.gamma << "," << err.theta << ","
                 << err_1st.price << "," << err_2nd.price << std::endl;
        }
    }
}