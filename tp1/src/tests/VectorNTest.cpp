#include <gtest/gtest.h>
#include "VectorN.h"

TEST(VectorNTest, Zeros)
{
    const auto v = mn::VectorNf::zeros(3);
    EXPECT_FLOAT_EQ(v(0), 0.0f);
    EXPECT_FLOAT_EQ(v(1), 0.0f);
    EXPECT_FLOAT_EQ(v(2), 0.0f);
}

TEST(VectorNTest, EqualOperator)
{
    const auto v = mn::VectorNf::zeros(3);
    mn::VectorNf zeros{0.0f, 0.0f, 0.0f};
    EXPECT_TRUE(v == zeros);
}
