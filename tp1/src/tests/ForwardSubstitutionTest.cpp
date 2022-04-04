#include <gtest/gtest.h>
#include "ForwardSubstitution.h"

TEST(ForwardSubstitutionTest, M22Identity)
{
    mn::MatrixNf A = { {1.0f, 0.0f }, {0.0f, 1.0f } };
    mn::VectorNf b = { 1.0f, 1.0f };
    mn::VectorNf x{ 0.0f, 0.0f };

    mn::ForwardSubstitution(A, b, x);

    EXPECT_FLOAT_EQ(A(0,0), 1.0f);
    EXPECT_FLOAT_EQ(A(1,0), 0.0f);
    EXPECT_FLOAT_EQ(A(0,1), 0.0f);
    EXPECT_FLOAT_EQ(A(1,1), 1.0f);

    EXPECT_FLOAT_EQ(b(0), 1.0f);
    EXPECT_FLOAT_EQ(b(1), 1.0f);

    EXPECT_FLOAT_EQ(x(0), 1.0f);
    EXPECT_FLOAT_EQ(x(1), 1.0f);
}