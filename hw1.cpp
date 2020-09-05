#include <iostream>
#include "src/analytical.h"
#include "src/BinomialPricer.h"
#include "src/BinomialPricer.cpp"
#include "src/AnalyticalPricer.h"
#include "src/AnalyticalPricer.cpp"
#include "src/common.h"

#include <Eigen/Dense>


using namespace std;
using namespace core;
using namespace analytical;
using namespace Eigen;


int main() {
    Params params{54, 50, 0.025, 0.01, 0.28, 1};
    cout << BinomialPricer<PutPayoff, PutPayoff, EuropeanStep>{params}.price({1024}) << endl;
    cout << BinomialAveragingPricer<PutPayoff, PutPayoff, EuropeanStep>{params}.price({1024}) << endl;
    cout << AnalyticalPricer<PutPayoff, EuropeanStep>{params}.price({}) << endl;
//    BinomialPricer<CallPayoff, CallPayoff, EuropeanStep>{params}.profile({2, 4, 8, 16, 32});
//    ArrayXd seq = pow(2, ArrayXd::LinSpaced(8, 0, 7)) * 10;
//    for (const auto& x : seq)
//        cout << x << endl;
//    cout << seq << endl;
    return 0;
}
