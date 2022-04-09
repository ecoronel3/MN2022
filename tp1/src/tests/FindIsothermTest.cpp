#include <gtest/gtest.h>
#include "FindIsotherm.h"

#include <iomanip>

namespace
{
    constexpr float pi = 3.141592653589793f;
}

TEST(FindIsothermTest, BuildEqSystem)
{
    // 4.5 5.5 5 6 500 1
    // 1500.0 1500.0 1500.0 1500.0 1500.0 1500.0 50.0 50.0 50.0 50.0 50.0 50.0

    const int n = 6;
    const int m = 4;
    const float ri = 4.0f;
    const float re = 5.0f;

    auto [A, b] = mn::BuildEqSystem(ri, re, m, n, 
        {1500.0f, 1500.0f, 1500.0f, 1500.0f, 1500.0f, 1500.0f},
        {50.0f, 50.0f, 50.0f, 50.0f, 50.0f, 50.0f});
    
    EXPECT_EQ(A.rows(), (m - 1) * n );
    EXPECT_EQ(A.cols(), (m - 1) * n );
    EXPECT_EQ(b.size(), (m - 1) * n );

    const float r1 = 4.25;
    const float delta_r = (re - ri) / static_cast<float>(m);
    const float sqDelta_r = delta_r * delta_r;

    const float delta_t = 2.0f*pi / static_cast<float>(n);
    const float sqDelta_t = delta_t*delta_t;

    // Termino independiente
    const float coef = r1*r1*sqDelta_t - r1*delta_r*sqDelta_t;
    const float b0 = -1500.f*coef;
    for(int i = 0; i < n; ++i)
    {
        EXPECT_FLOAT_EQ(b(i),  b0);
    }
    
    // TODO check zeros

    const float r3 = 4.75f;
    const float bnm2 = -50.f*(r3*r3*sqDelta_t);
    for(int i = 0; i < n; ++i)
    {
        EXPECT_FLOAT_EQ(b(n*(m - 2) + i),  bnm2);
    }
    
    // matriz
    EXPECT_FLOAT_EQ(A(0, 0),  -2.0f*r1*r1*sqDelta_t + r1*delta_r*sqDelta_t - 2.0f*sqDelta_r );
    EXPECT_FLOAT_EQ(A(0, 1), sqDelta_r);
    EXPECT_FLOAT_EQ(A(0, 2),  0.0f);
    EXPECT_FLOAT_EQ(A(0, 3),  0.0f);
    EXPECT_FLOAT_EQ(A(0, 4),  0.0f);
    EXPECT_FLOAT_EQ(A(0, 5), sqDelta_r);
    EXPECT_FLOAT_EQ(A(0, 6), r1*r1*sqDelta_t);
    
    // std::cout << b << '\n';
    // std::cout << std::fixed << std::setprecision(3) << A << '\n';

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

    EXPECT_FLOAT_EQ(output.soluciones[0](0), 1500.0f);
    EXPECT_FLOAT_EQ(output.soluciones[0](6), 750.0f);
    EXPECT_FLOAT_EQ(output.soluciones[0](17), 100.0f);
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

    EXPECT_FLOAT_EQ(output.soluciones[0](0), 1500.0f);
    EXPECT_FLOAT_EQ(output.soluciones[0](6), 750.0f);
    EXPECT_FLOAT_EQ(output.soluciones[0](17), 100.0f);

    std::cout << output.soluciones[0] ;
}
