//
// Created by Albert Wong on 9/6/20.
//
#include "header.h"

using namespace core;


TEST(General, PricingOutput) {
    PricingOutput<> out1{EmptyTag(), 1, 2, 3, 4};
    PricingOutput<> out2{EmptyTag(), 3, 3, 3, 3};

    // Test addition
    auto out = out1 + out2;
    EXPECT_EQ(out.price, 4);
    EXPECT_EQ(out.delta, 5);
    EXPECT_EQ(out.gamma, 6);
    EXPECT_EQ(out.theta, 7);

    // Test subtraction
    out = out1 - out2;
    EXPECT_EQ(out.price, -2);
    EXPECT_EQ(out.delta, -1);
    EXPECT_EQ(out.gamma, 0);
    EXPECT_EQ(out.theta, 1);

    // Test product
    out = out1 * 3;
    EXPECT_EQ(out.price, 3);
    EXPECT_EQ(out.delta, 6);
    EXPECT_EQ(out.gamma, 9);
    EXPECT_EQ(out.theta, 12);

    out = -2 * out1;
    EXPECT_EQ(out.price, -2);
    EXPECT_EQ(out.delta, -4);
    EXPECT_EQ(out.gamma, -6);
    EXPECT_EQ(out.theta, -8);

    // Test division
    out = out2 / 2;
    EXPECT_EQ(out.price, 1.5);
    EXPECT_EQ(out.delta, 1.5);
    EXPECT_EQ(out.gamma, 1.5);
    EXPECT_EQ(out.theta, 1.5);

    // Integration 1
    out = (out1 + out2) / 2;
    EXPECT_EQ(out.price, 2);
    EXPECT_EQ(out.delta, 2.5);
    EXPECT_EQ(out.gamma, 3);
    EXPECT_EQ(out.theta, 3.5);

    // Integration 2
    out = 2 * out1 - out2;
    EXPECT_EQ(out.price, -1);
    EXPECT_EQ(out.delta, 1);
    EXPECT_EQ(out.gamma, 3);
    EXPECT_EQ(out.theta, 5);
}