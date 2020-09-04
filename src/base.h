//
// Created by Albert Wong on 9/3/20.
//

#ifndef HW1_BASE_H
#define HW1_BASE_H

#include <type_traits>
#include <ostream>
#include <limits>
#include <Eigen/Dense>

using namespace Eigen;


namespace core {

    struct Params {
        double s;
        double k;
        double r;
        double q;
        double sig;
        double t;
    };

    template <typename TagT>
    struct PricingOutput {
        TagT tag;
        double price, delta, gamma, theta;

        friend std::ostream &operator<<(std::ostream &os, const PricingOutput &output) {
            os << output.tag << "," << output.price << "," << output.delta << "," << output.gamma << "," << output.theta;
            return os;
        }
    };

    struct EmptyTag {
        friend std::ostream &operator<<(std::ostream &os, const EmptyTag &tag) {
            return os;
        }
    };

    class Parameterized {
    protected:
        Params params_;

    public:
        explicit Parameterized(const Params &params) : params_(params) {};
    };

    struct Payoff : Parameterized {
        explicit Payoff(const Params &params) : Parameterized(params) {}
        virtual ArrayXd operator()(ArrayXd s) = 0;
    };

    struct Stepback : Parameterized {
        explicit Stepback(const Params &params) : Parameterized(params) {}
        virtual ArrayXd operator()(ArrayXd values, ArrayXd s, Payoff intrinsic_func) = 0;
    };

    template <typename PayoffT, typename IntrinsicT, typename StepbackT, typename TagT=EmptyTag>
    class Pricer : public Parameterized{
    protected:
        const double UNDEFINED = std::numeric_limits<double>::quiet_NaN();
        PayoffT payoff_;
        IntrinsicT intrinsic_;
        StepbackT stepback_;

    public:
        explicit Pricer(const Params& params) : Parameterized(params),
            payoff_(PayoffT(params)), intrinsic_(IntrinsicT(params)), stepback_(StepbackT(params)) {

            static_assert(std::is_base_of<Payoff, PayoffT>::value, "PayoffT must be subclass of Payoff");
            static_assert(std::is_base_of<Payoff, IntrinsicT>::value, "IntrinsicT must be subclass of Payoff");
            static_assert(std::is_base_of<Stepback, StepbackT>::value, "StepbackT must be subclass of Stepback");
        };

        virtual PricingOutput<TagT> price(TagT tag) = 0;
    };

}

#endif //HW1_BASE_H
