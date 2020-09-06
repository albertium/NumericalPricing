//
// Created by Albert Wong on 9/6/20.
//
#include <iostream>
#include "gtest/gtest.h"
#include "core.h"

using namespace std;
using namespace core;


TEST(BinomialTree, AnalyticalCall) {
    // Benchmark against FlexPricer

    Params params{54, 50, 0.025, 0.01, 0.28, 1};

    // Call test
    PricingOutput<> output = AnalyticalPricer<CallPayoff, EuropeanStep>{params}.price({});
    cout << output;
    // FIXME Accuracy is too low
    EXPECT_NEAR(output.price, 8.341605186462402, 1e-5);
    EXPECT_NEAR(output.delta, 0.673493623733521, 1e-7);
    EXPECT_NEAR(output.gamma, 0.023408144712448, 1e-7);
    EXPECT_NEAR(output.theta, -3.012708902359009, 1e-7);
}


TEST(BinomialTree, AnalyticalPut) {
    // Benchmark against FlexPricer

    Params params{54, 50, 0.025, 0.01, 0.28, 1};

    // Put test
    PricingOutput<> output = AnalyticalPricer<PutPayoff, EuropeanStep>{params}.price({});
    EXPECT_NEAR(output.price, 3.6444083750987026, 1e-12);
    EXPECT_NEAR(output.delta, -0.316556274890900, 1e-7);
    EXPECT_NEAR(output.gamma, 0.023408144712448, 1e-7);
    EXPECT_NEAR(output.theta, -2.328198432922363, 1e-7);
}
