//
// Created by Albert Wong on 9/6/20.
//
#include <iostream>
#include "header.h"

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


TEST(BinomialTree, Call) {
    // Vanilla binomial call test, benchmarked against FlexPricer

    Params params{54, 50, 0.025, 0.01, 0.28, 1};

    // Put test
    PricingOutput<TreeTag> output = BinomialPricer<CallPayoff, CallPayoff, EuropeanStep>{params}.price({15000});
    EXPECT_NEAR(output.price, 8.341605186462402, 1e-5);
    EXPECT_NEAR(output.delta, 0.673493623733521, 1e-6);
    EXPECT_NEAR(output.gamma, 0.023408144712448, 1e-6);
    EXPECT_NEAR(output.theta, -3.012708902359009, 1e-4);
}


TEST(BinomialTree, Put) {
    // Vanilla binomial put test, benchmarked against FlexPricer

    Params params{54, 50, 0.025, 0.01, 0.28, 1};

    // Put test
    PricingOutput<TreeTag> output = BinomialPricer<PutPayoff, PutPayoff, EuropeanStep>{params}.price({15000});
    EXPECT_NEAR(output.price, 3.6444083750987026, 1e-4);
    EXPECT_NEAR(output.delta, -0.316556274890900, 1e-6);
    EXPECT_NEAR(output.gamma, 0.023408144712448, 1e-6);
    EXPECT_NEAR(output.theta, -2.328198432922363, 1e-4);
}


TEST(BinomialTree, AveragePut) {
    // Vanilla binomial put test, benchmarked against FlexPricer

    Params params{54, 50, 0.025, 0.01, 0.28, 1};

    // Put test
    PricingOutput<TreeTag> output = BinomialAveragingPricer<PutPayoff, PutPayoff, EuropeanStep>{params}.price({10000});
    EXPECT_NEAR(output.price, 3.6444083750987026, 1e-4);
    EXPECT_NEAR(output.delta, -0.316556274890900, 1e-6);
    EXPECT_NEAR(output.gamma, 0.023408144712448, 1e-6);
    EXPECT_NEAR(output.theta, -2.328198432922363, 1e-3);
}


TEST(BinomialTree, BBSPut) {
    // Binomial BS put test, benchmarked against FlexPricer

    Params params{54, 50, 0.025, 0.01, 0.28, 1};
    PricingOutput<TreeTag> output = BinomialBSPricer<PutPayoff, PutPayoff, EuropeanStep>{params}.price({10000});
    EXPECT_NEAR(output.price, 3.6444083750987026, 1e-4);
    EXPECT_NEAR(output.delta, -0.316556274890900, 1e-6);
    EXPECT_NEAR(output.gamma, 0.023408144712448, 1e-6);
    EXPECT_NEAR(output.theta, -2.328198432922363, 1e-3);
}


TEST(BinomialTree, BBSRPut) {
    // Binomial BS put test, benchmarked against FlexPricer
    Params params{54, 50, 0.025, 0.01, 0.28, 1};
    PricingOutput<TreeTag> output = BinomialBSRPricer<PutPayoff, PutPayoff, EuropeanStep>{params}.price({1024});
    EXPECT_NEAR(output.price, 3.6444083750987026, 1e-4);
    EXPECT_NEAR(output.delta, -0.316556274890900, 1e-6);
    EXPECT_NEAR(output.gamma, 0.023408144712448, 1e-7);
    EXPECT_NEAR(output.theta, -2.328198432922363, 1e-5);
}


TEST(BinomialTree, AmericanPut) {
    // Vanilla binomial put test, benchmarked against FlexPricer

    Params params{54, 50, 0.025, 0.01, 0.28, 1};
    PricingOutput<TreeTag> output = BinomialPricer<PutPayoff, PutPayoff, AmericanStep>{params}.price({1024});
    EXPECT_NEAR(output.price, 3.6919396578539305, 1e-10);
    EXPECT_NEAR(output.delta, -0.32217533880631716, 1e-10);
    EXPECT_NEAR(output.gamma, 0.02408512942851285, 1e-10);
    EXPECT_NEAR(output.theta, -2.399949808859219, 1e-10);
}