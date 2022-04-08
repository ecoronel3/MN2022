#include <gtest/gtest.h>
#include "LUFactorization.h"

TEST(LUFactorizationTest, A33Identity)
{
    const int n = 3;
    const auto A = mn::MatrixNf::identity(n);
    
    const auto [L, U] = mn::LUFactorization(A);

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            EXPECT_FLOAT_EQ(L(i, j), i == j ? 1.0f : 0.0f);
        }
    }

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            EXPECT_FLOAT_EQ(U(i, j), i == j ? 1.0f : 0.0f);
        }
    }
}

TEST(LUFactorizationTest, APractica2Ej2)
{
    const mn::MatrixNf A{ 
        {1.0f, 2.0f, 3.0f, 4.0f},
        {1.0f, 4.0f, 9.0f, 16.0f},
        {1.0f, 8.0f, 27.0f, 64.0f},
        {1.0f, 16.0f, 81.0f, 256.0f},
     };

    mn::MatrixNf L{4};
    mn::MatrixNf U{4};

    mn::LUFactorization(A, L, U);

    const mn::MatrixNf expectedL{
        {1.0f, 0.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 0.0f, 0.0f},
        {1.0f, 3.0f, 1.0f, 0.0f},
        {1.0f, 7.0f, 6.0f, 1.0f},
    };

    const mn::MatrixNf expectedU{
        {1.0f, 2.0f, 3.0f, 4.0f},
        {0.0f, 2.0f, 6.0f, 12.0f},
        {0.0f, 0.0f, 6.0f, 24.0f},
        {0.0f, 0.0f, 0.0f, 24.0f},
    };

    EXPECT_EQ(L, expectedL);
    EXPECT_EQ(U, expectedU);
}

TEST(LUFactorizationTest, APractica2Ej4b)
{
    const mn::MatrixNf A{ 
        { 2.0f, 1.0f, 2.0f },
        { 1.0f, 2.0f, 3.0f },
        { 4.0f, 1.0f, 2.0f }
    };

    auto [L, U] = mn::LUFactorization(A);

    const mn::MatrixNf expectedL{
        {1.0f, 0.0f, 0.0f},
        {0.5f, 1.0f, 0.0f},
        {2.0f, -2.0f/3.0f, 1.0f}
    };

    const mn::MatrixNf expectedU{
        {2.0f, 1.0f, 2.0f},
        {0.0f, 3.0f/2.0f, 2.0f},
        {0.0f, 0.0f, -2.0f/3.0f}
    };

    EXPECT_EQ(L, expectedL);
    EXPECT_EQ(U, expectedU);
}