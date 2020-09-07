#include <vector>
#include "core.h"

using namespace std;
using namespace core;


int main() {
    Params params{54, 50, 0.025, 0.01, 0.28, 1};
    vector<TreeTag> steps{10, 20, 40, 80, 160, 320, 640, 1280};

    // European
    PricingOutput<> euro_exact = AnalyticalPricer<PutPayoff, EuropeanStep>{params}.price({});
    BinomialPricer<PutPayoff, PutPayoff, EuropeanStep>{params}.profile(steps, euro_exact, "euro_1");
    BinomialAveragingPricer<PutPayoff, PutPayoff, EuropeanStep>{params}.profile(steps, euro_exact, "euro_2_avg");
    BinomialBSPricer<PutPayoff, PutPayoff, EuropeanStep>{params}.profile(steps, euro_exact, "euro_3_bbs");
    BinomialBSRPricer<PutPayoff, PutPayoff, EuropeanStep>{params}.profile(steps, euro_exact, "euro_4_bssr");

    // American
    PricingOutput<TreeTag> tmp = BinomialAveragingPricer<PutPayoff, PutPayoff, AmericanStep>{params}.price({10000});
    PricingOutput<> amer_exact{EmptyTag{}, tmp.price, tmp.delta, tmp.gamma, tmp.theta};
    BinomialPricer<PutPayoff, PutPayoff, AmericanStep>{params}.profile(steps, amer_exact, "amer_1");
    BinomialAveragingPricer<PutPayoff, PutPayoff, AmericanStep>{params}.profile(steps, amer_exact, "amer_2_avg");
    BinomialBSPricer<PutPayoff, PutPayoff, AmericanStep>{params}.profile(steps, amer_exact, "amer_3_bbs");
    BinomialBSRPricer<PutPayoff, PutPayoff, AmericanStep>{params}.profile(steps, amer_exact, "amer_4_bssr");
    return 0;
}
