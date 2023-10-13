
#include <gtest/gtest.h>
#include "pricingutil.h"


TEST(sampleTest, sample) {
    EXPECT_EQ(4, 4);
}

TEST(PricingUtilTest, normalCalc) {
    PricingUtil util;
    float result = util.calcVal(100.0f, 0.05f, 2.0f);
    EXPECT_NEAR(result, 190.0f, 1e-6); // 100 * 0.95 * 2
}

TEST(PricingUtilTest, zeroInterest) {
    PricingUtil util;
    float result = util.calcVal(100.0f, 0.0f, 2.0f);
    EXPECT_NEAR(result, 180.0f, 1e-6);  // 100 * 0.9 * 2 = 180
}

TEST(PricingUtilTest, zeroPrevPrice) {
    PricingUtil util;
    float result = util.calcVal(0.0f, 0.05f, 2.0f);
    EXPECT_NEAR(result, 0.0f, 1e-6);
}

TEST(PricingUtilTest, negativeInterest) {
    PricingUtil util;
    float result = util.calcVal(100.0f, -0.05f, 2.0f);
    EXPECT_NEAR(result, 170.0f, 1e-6);  // 100 * 0.85 * 2 = 170
}

TEST(PricingUtilTest, negPrice) {
    PricingUtil util;
    float result = util.calcVal(-100.0f, 0.05f, 2.0f);
    EXPECT_NEAR(result, -190.0f, 1e-6);  // -100 * 0.95 * 2 = -190
}

TEST(PricingUtilTest, zeroOleo) {
    PricingUtil util;
    float result = util.calcVal(100.0f, 0.05f, 0.0f);
    EXPECT_NEAR(result, 0.0f, 1e-6);
}

TEST(PricingUtilTest, bigOleo) {
    PricingUtil util;
    float result = util.calcVal(100.0f, 0.05f, 1e6f);
    EXPECT_NEAR(result, 95000000.0f, 1e-6);  // 100 * 0.95 * 1e6 = 95000000
}

TEST(PricingUtilTest, getValTest) {
    PricingUtil util;
    util.calcVal(100.0f, 0.05f, 2.0f);
    float value = util.getVal();
    EXPECT_NEAR(value, 190.0f, 1e-6);
}