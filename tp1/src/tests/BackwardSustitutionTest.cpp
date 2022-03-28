#include <gtest/gtest.h>
#include "BackwardSustitution.h"

TEST(BackwardSustitutionTest, M22Identity)
{
    mn::MatrixNf A = { {1.0f, 0.0f }, {0.0f, 1.0f } };
    mn::VectorNf b = { 1.0f, 1.0f };
    mn::VectorNf x { 0.0f, 0.0f };

    mn::BackwardSubstitution(A, b, x);

    EXPECT_FLOAT_EQ(A(0, 0), 1.0f);
    EXPECT_FLOAT_EQ(A(0, 1), 0.0f);
    EXPECT_FLOAT_EQ(A(1, 0), 0.0f);
    EXPECT_FLOAT_EQ(A(1, 1), 1.0f);

    EXPECT_FLOAT_EQ(b(0), 1.0f);
    EXPECT_FLOAT_EQ(b(1), 1.0f);

    EXPECT_FLOAT_EQ(x(0), 1.0f);
    EXPECT_FLOAT_EQ(x(1), 1.0f);
}

TEST(BackwardSustitutionTest, M33Diagonal)
{
    mn::MatrixNf A = { { 2.0f, 0.0f, 0.0f }, { 0.0f, 5.0f, 0.0f }, { 0.0f, 0.0f, 3.0f } };
    mn::VectorNf b = { 1.0f, 15.0f, 6.0f };
    mn::VectorNf x{ 0.0f, 0.0f, 0.0f };

    mn::BackwardSubstitution(A, b, x);

    EXPECT_FLOAT_EQ(A(0, 0), 2.0f);
    EXPECT_FLOAT_EQ(A(0, 1), 0.0f);
    EXPECT_FLOAT_EQ(A(0, 2), 0.0f);
    EXPECT_FLOAT_EQ(A(1, 0), 0.0f);
    EXPECT_FLOAT_EQ(A(1, 1), 5.0f);
    EXPECT_FLOAT_EQ(A(1, 2), 0.0f);
    EXPECT_FLOAT_EQ(A(2, 0), 0.0f);
    EXPECT_FLOAT_EQ(A(2, 1), 0.0f);
    EXPECT_FLOAT_EQ(A(2, 2), 3.0f);

    EXPECT_FLOAT_EQ(b(0), 1.0f);
    EXPECT_FLOAT_EQ(b(1), 15.0f);
    EXPECT_FLOAT_EQ(b(2), 6.0f);

    EXPECT_FLOAT_EQ(x(0), 0.5f);
    EXPECT_FLOAT_EQ(x(1), 3.0f);
    EXPECT_FLOAT_EQ(x(2), 2.0f);
}


TEST(BackwardSustitutionTest, M44)
{
    mn::MatrixNf A = {  { 2.0f, 0.0f, 0.0f, 10.0f },
                        { 0.0f, 4.0f, 0.0f, 1.0f },
                        { 0.0f, 0.0f, 3.0f, 1.0f },
                        { 0.0f, 0.0f, 0.0f, 1.0f }, };
    mn::VectorNf b = { 61.0f, 14.0f, 9.0f, 6.0f };
    mn::VectorNf x{ 0.0f, 0.0f, 0.0f, 0.0f };

    mn::BackwardSubstitution(A, b, x);

    EXPECT_FLOAT_EQ(x(0), 0.5f);
    EXPECT_FLOAT_EQ(x(1), 2.0f);
    EXPECT_FLOAT_EQ(x(2), 1.0f);
    EXPECT_FLOAT_EQ(x(3), 6.0f);
}
