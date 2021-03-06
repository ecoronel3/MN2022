#include <gtest/gtest.h>
#include "FindIsotherm.h"

#include <iomanip>

namespace
{
    constexpr double pi = 3.141592653589793;
}

TEST(FindIsothermTest, BuildMatrix)
{
    const int n = 6;
    const int m = 4;
    const double ri = 4.0f;
    const double re = 5.0f;

    auto A = mn::BuildMatrix(ri, re, m, n);
    
    EXPECT_EQ(A.rows(), (m - 1) * n );
    EXPECT_EQ(A.cols(), (m - 1) * n );

    const double r1 = 4.25;
    const double delta_r = (re - ri) / static_cast<double>(m);
    const double sqDelta_r = delta_r * delta_r;

    const double delta_t = 2.0f*pi / static_cast<double>(n);
    const double sqDelta_t = delta_t*delta_t;
    
    // matriz
    EXPECT_DOUBLE_EQ(A(0, 0),  -2.0f*r1*r1*sqDelta_t + r1*delta_r*sqDelta_t - 2.0f*sqDelta_r );
    EXPECT_DOUBLE_EQ(A(0, 1), sqDelta_r);
    EXPECT_DOUBLE_EQ(A(0, 2),  0.0f);
    EXPECT_DOUBLE_EQ(A(0, 3),  0.0f);
    EXPECT_DOUBLE_EQ(A(0, 4),  0.0f);
    EXPECT_DOUBLE_EQ(A(0, 5), sqDelta_r);
    EXPECT_DOUBLE_EQ(A(0, 6), r1*r1*sqDelta_t);
}

TEST(FindIsothermTest, BuildVector)
{
    const int n = 6;
    const int m = 4;
    const double ri = 4.0f;
    const double re = 5.0f;

    auto b = mn::BuildVector(ri, re, m, n, 
        { 1500.0f, 1500.0f, 1500.0f, 1500.0f, 1500.0f, 1500.0f },
        { 50.0f, 50.0f, 50.0f, 50.0f, 50.0f, 50.0f });
    
    EXPECT_EQ(b.size(), (m - 1) * n );

    const double r1 = 4.25;
    const double delta_r = (re - ri) / static_cast<double>(m);
    const double sqDelta_r = delta_r * delta_r;

    const double delta_t = 2.0f*pi / static_cast<double>(n);
    const double sqDelta_t = delta_t*delta_t;

    // Termino independiente
    const double coef = r1*r1*sqDelta_t - r1*delta_r*sqDelta_t;
    const double b0 = -1500.f*coef;
    for(int i = 0; i < n; ++i)
    {
        EXPECT_DOUBLE_EQ(b(i),  b0);
    }

    const double r3 = 4.75f;
    const double bnm2 = -50.f*(r3*r3*sqDelta_t);
    for(int i = 0; i < n; ++i)
    {
        EXPECT_DOUBLE_EQ(b(n*(m - 2) + i),  bnm2);
    }
}

TEST(FindIsothermTest, FindIsothermGE)
{
    mn::InputParams input;
    input.ri = 4.0f;
    input.re = 5.0f;
    input.n = 6;
    input.m = 4;
    input.iso = 500.0f;
    input.ninst = 1;
    input.instances.emplace_back(
        mn::Instance{
            {1500.0f, 1500.0f, 1500.0f, 1500.0f, 1500.0f, 1500.0f},
            {50.0f, 50.0f, 50.0f, 50.0f, 50.0f, 50.0f}
        }
    );

    mn::OutputParams output;
    mn::FindIsotherm(0, input, output);

    EXPECT_DOUBLE_EQ(output.temps[0].inner(0), 1105.138173302108);
    EXPECT_DOUBLE_EQ(output.temps[0].inner(6), 733.50351288056254);
    EXPECT_DOUBLE_EQ(output.temps[0].inner(17), 382.51522248243566);
}

TEST(FindIsothermTest, FindIsothermLU)
{
    mn::InputParams input;
    input.ri = 4.0f;
    input.re = 5.0f;
    input.n = 6;
    input.m = 4;
    input.iso = 500.0f;
    input.ninst = 1;
    input.instances.emplace_back(
        mn::Instance{
            {1500.0f, 1500.0f, 1500.0f, 1500.0f, 1500.0f, 1500.0f},
            {50.0f, 50.0f, 50.0f, 50.0f, 50.0f, 50.0f}
        }
    );

    mn::OutputParams output;
    mn::FindIsotherm(1, input, output);

    EXPECT_DOUBLE_EQ(output.temps[0].inner(0), 1105.138173302108);
    EXPECT_DOUBLE_EQ(output.temps[0].inner(6), 733.50351288056254);
    EXPECT_DOUBLE_EQ(output.temps[0].inner(17), 382.51522248243566);
}
