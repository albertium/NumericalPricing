#include <iostream>
#include <vector>

#include "include/core.h"

using namespace std;
using namespace core;
using namespace Eigen;


int main() {
    Params params{54, 50, 0.025, 0.01, 0.28, 1};
    vector<TreeTag> steps{10, 20, 40, 80, 160, 320, 640, 1280};
    cout << AnalyticalPricer<PutPayoff, EuropeanStep>{params}.price({}) << endl;
    BinomialPricer<PutPayoff, PutPayoff, EuropeanStep>{params}.profile(steps, "vanilla");
    BinomialAveragingPricer<PutPayoff, PutPayoff, EuropeanStep>{params}.profile(steps, "average");
    BinomialBSPricer<PutPayoff, PutPayoff, EuropeanStep>{params}.profile(steps, "bss");

//    BinomialPricer<CallPayoff, CallPayoff, EuropeanStep>{params}.profile({2, 4, 8, 16, 32});
//    ArrayXd seq = pow(2, ArrayXd::LinSpaced(8, 0, 7)) * 10;
//    for (const auto& x : seq)
//        cout << x << endl;
//    cout << seq << endl;
    return 0;
}
