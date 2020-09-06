#include <iostream>
#include <vector>

#include "core.h"

using namespace std;
using namespace core;


int main() {
    Params params{54, 50, 0.025, 0.01, 0.28, 1};
    vector<TreeTag> steps{10, 20, 40, 80, 160, 320, 640};
    cout << AnalyticalPricer<PutPayoff, EuropeanStep>{params}.price({}) << endl;
    BinomialPricer<PutPayoff, PutPayoff, EuropeanStep>{params}.profile(steps, "vanilla");
    BinomialAveragingPricer<PutPayoff, PutPayoff, EuropeanStep>{params}.profile(steps, "average");
    BinomialBSPricer<PutPayoff, PutPayoff, EuropeanStep>{params}.profile(steps, "bss");
    return 0;
}
