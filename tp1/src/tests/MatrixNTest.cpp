#include <gtest/gtest.h>
#include "MatrixN.h"

TEST(MatrixNTest, Zeros)
{
    const int n = 7;
    auto m = mn::MatrixNf::zeros(n);
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            EXPECT_FLOAT_EQ(m(i, j), 0.0f);
        }
    }
}

TEST(MatrixNTest, Identity)
{
    const int n = 10;
    auto m = mn::MatrixNf::identity(n);
    for(int i = 0; i < n; ++i)
    {
        EXPECT_FLOAT_EQ(m(i, i), 1.0f);
        for(int j = 0; j < n; ++j)
        {
            if (i == j)
            {
                continue;
            }
            EXPECT_FLOAT_EQ(m(i, j), 0.0f);
        }
    }
}

TEST(MatrixNTest, Copy)
{
    const int n = 4;
    auto A = mn::MatrixNf::identity(n);
    A(0, 0) = 2.0f;

    const auto B = A;
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            EXPECT_FLOAT_EQ(A(i, j), B(i, j));
        }
    }
}
