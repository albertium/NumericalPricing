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

    // ========== Parameterizable ==========
    // Params is used to parameterize a Parameterizable
    struct Params {
        double s, k, r, q, sig, t;
    };

    // ========== Parameterizable ==========
    // Parameterized represents class that can be parameterized
    class Parameterizable {
    protected:
        Params params_;

    public:
        explicit Parameterizable(const Params &params) : params_(params) {};
    };

    // ========== Tag Base Class ==========
    // Tag is the header of pricing output
    struct Tag {
        virtual void write_to_stream(std::ostream &os) const = 0;

        virtual std::string header() const = 0;

        friend std::ostream &operator<<(std::ostream &os, const Tag &tag) {
            tag.write_to_stream(os);
            return os;
        }
    };

    // ========== Default Tag Class ==========
    struct EmptyTag : public Tag {
        void write_to_stream(std::ostream &os) const override { os << -1; }

        std::string header() const override { return "Tag"; }
    };

    template<typename TagT>
    struct PricingOutput {
        TagT tag;
        double price, delta, gamma, theta;

        PricingOutput<TagT> operator+(const PricingOutput<TagT> &other);

        friend std::ostream &operator<<(std::ostream &os, const PricingOutput &output) {
            os << output.tag << std::setprecision(6) << std::fixed
               << "," << output.price << "," << output.delta << "," << output.gamma << "," << output.theta;
            return os;
        }
    };


    // ========== Payoff Function Base Class ==========
    struct Payoff : Parameterizable {
        explicit Payoff(const Params &params) : Parameterizable(params) {}

        virtual ArrayXd operator()(const ArrayXd &s) const = 0;
    };


    // ========== Stepback Function Base Class ==========
    struct Stepback : Parameterizable {
        explicit Stepback(const Params &params) : Parameterizable(params) {}

        virtual ArrayXd operator()(const ArrayXd &values, const ArrayXd &s, const Payoff *adjust_func) const = 0;
    };


    // ========== Pricer Base Class ==========
    template<typename PayoffT, typename AdjustT, typename StepbackT, typename TagT=EmptyTag>
    class Pricer : public Parameterizable {
    protected:
        const double UNDEFINED = std::numeric_limits<double>::quiet_NaN();
        PayoffT payoff_;
        std::unique_ptr<AdjustT> adjust_;
        StepbackT stepback_;

    public:
        explicit Pricer(const Params &params);

        virtual PricingOutput<TagT> price(const TagT &tag) = 0;

        void profile(const std::vector<TagT> &tags, const std::string &name);
    };
}

#endif //HW1_BASE_H
