//
// Created by Albert Wong on 9/3/20.
//

#ifndef HW1_BASE_H
#define HW1_BASE_H

#include <type_traits>
#include <fstream>
#include <vector>
#include <iomanip>
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

    struct Tag {
        friend std::ostream &operator<<(std::ostream &os, const Tag &tag) {
            tag.write_to_stream(os);
            return os;
        }

        virtual void write_to_stream(std::ostream& os) const = 0;

        virtual std::string header() const = 0;
    };

    template<typename TagT>
    struct PricingOutput {
        TagT tag;
        double price, delta, gamma, theta;

        PricingOutput<TagT> operator+(const PricingOutput<TagT> &other) {
            return {tag,
                    (price + other.price) / 2,
                    (delta + other.delta) / 2,
                    (gamma + other.gamma) / 2,
                    (theta + other.theta) / 2};
        }

        friend std::ostream &operator<<(std::ostream &os, const PricingOutput &output) {
            os << output.tag << std::setprecision(6) << std::fixed
               << "," << output.price << "," << output.delta << "," << output.gamma << "," << output.theta;
            return os;
        }
    };

    struct EmptyTag : public Tag {
        void write_to_stream(std::ostream &os) const override {
            os << -1;
        }

        std::string header() const override {
            return "Tag";
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

        virtual ArrayXd operator()(const ArrayXd &s) = 0;
    };

    struct Stepback : Parameterized {
        explicit Stepback(const Params &params) : Parameterized(params) {}

        virtual ArrayXd operator()(const ArrayXd &values, const ArrayXd &s, std::shared_ptr<Payoff> adjust_func) = 0;
    };

    template<typename PayoffT, typename AdjustT, typename StepbackT, typename TagT=EmptyTag>
    class Pricer : public Parameterized {
    protected:
        const double UNDEFINED = std::numeric_limits<double>::quiet_NaN();
        PayoffT payoff_;
        std::shared_ptr<Payoff> adjust_;
        StepbackT stepback_;

    public:
        explicit Pricer(const Params &params) : Parameterized(params),
                                                payoff_(PayoffT(params)),
                                                adjust_(std::make_shared<AdjustT>(params)),
                                                stepback_(StepbackT(params)) {

            static_assert(std::is_base_of<Payoff, PayoffT>::value, "PayoffT must be subclass of Payoff");
            static_assert(std::is_base_of<Payoff, AdjustT>::value, "AdjustT must be subclass of Payoff");
            static_assert(std::is_base_of<Stepback, StepbackT>::value, "StepbackT must be subclass of Stepback");
            static_assert(std::is_base_of<Tag, TagT>::value, "TagT must be subclass of Tag");
        };

        virtual PricingOutput<TagT> price(const TagT &tag) = 0;

        void profile(const std::vector<TagT> &tags, const std::string &name);
    };
}

#endif //HW1_BASE_H
