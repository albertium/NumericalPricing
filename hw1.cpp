#include <iostream>
#include "src/analytical.h"
#include "src/BinomialPricer.h"
#include "src/BinomialPricer.cpp"
#include "src/AnalyticalPricer.h"
#include "src/AnalyticalPricer.cpp"
#include "src/common.h"


using namespace std;
using namespace core;
using namespace analytical;


int main() {
    Params params{29, 33, 0.02, 0, 0.22, 0.5};
    cout << BinomialPricer<PutPayoff, PutPayoff, EuropeanStep>{params}.price({1024}) << endl;
    cout << AnalyticalPricer<PutPayoff, EuropeanStep>{params}.price({}) << endl;
    cout << PriceBlackScholesPut(29, 33, 0.02, 0, 0.22, 0.5) << endl;
    return 0;
}
