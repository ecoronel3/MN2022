#include <gtest/gtest.h>
#include "GaussianElimination.h"

TEST(GaussianElimination, M22Identity)
{
    mn::MatrixNf A = { {1.0f, 0.0f }, {0.0f, 1.0f } };
    mn::VectorNf b = { 1.0f, 1.0f };

    mn::GaussianElimination(A, b);

    EXPECT_FLOAT_EQ(A(0, 0), 1.0f);
    EXPECT_FLOAT_EQ(A(0, 1), 0.0f);
    EXPECT_FLOAT_EQ(A(1, 0), 0.0f);
    EXPECT_FLOAT_EQ(A(1, 1), 1.0f);

    EXPECT_FLOAT_EQ(b(0), 1.0f);
    EXPECT_FLOAT_EQ(b(1), 1.0f);
}


TEST(GaussianElimination, M33Diagonal)
{
    mn::MatrixNf A = { {2.0f, 0.0f, 0.0f }, {0.0f, 3.0f, 0.0f }, {0.0f, 0.0f, 4.0f } };
    mn::VectorNf b = { 1.0f, 2.0f, 3.0f };

    mn::GaussianElimination(A, b);

    EXPECT_FLOAT_EQ(A(0, 0), 2.0f);
    EXPECT_FLOAT_EQ(A(0, 1), 0.0f);
    EXPECT_FLOAT_EQ(A(0, 2), 0.0f);
    EXPECT_FLOAT_EQ(A(1, 0), 0.0f);
    EXPECT_FLOAT_EQ(A(1, 1), 3.0f);
    EXPECT_FLOAT_EQ(A(1, 2), 0.0f);
    EXPECT_FLOAT_EQ(A(2, 0), 0.0f);
    EXPECT_FLOAT_EQ(A(2, 1), 0.0f);
    EXPECT_FLOAT_EQ(A(2, 2), 4.0f);

    EXPECT_FLOAT_EQ(b(0), 1.0f);
    EXPECT_FLOAT_EQ(b(1), 2.0f);
    EXPECT_FLOAT_EQ(b(2), 3.0f);
}

TEST(GaussianElimination, M44)
{
    mn::MatrixNf A = {  { 1.0f, 0.0f, 2.0f, 2.0f },
                            { 1.0f, 1.0f, 3.0f, 0.0f },
                            { 1.0f, -1.0f, 3.0f, 2.0f },
                            { 1.0f, 2.0f, 2.0f, 3.0f } };

    mn::VectorNf b = { 1.0f, 2.0f, 3.0f, 4.0f };

    mn::GaussianElimination(A, b);

    EXPECT_FLOAT_EQ(A(0, 0), 1.0f);
    EXPECT_FLOAT_EQ(A(0, 1), 0.0f);
    EXPECT_FLOAT_EQ(A(0, 2), 2.0f);
    EXPECT_FLOAT_EQ(A(0, 3), 2.0f);
    EXPECT_FLOAT_EQ(A(1, 0), 0.0f);
    EXPECT_FLOAT_EQ(A(1, 1), 1.0f);
    EXPECT_FLOAT_EQ(A(1, 2), 1.0f);
    EXPECT_FLOAT_EQ(A(1, 3), -2.0f);
    EXPECT_FLOAT_EQ(A(2, 0), 0.0f);
    EXPECT_FLOAT_EQ(A(2, 1), 0.0f);
    EXPECT_FLOAT_EQ(A(2, 2), 2.0f);
    EXPECT_FLOAT_EQ(A(2, 3), -2.0f);
    EXPECT_FLOAT_EQ(A(3, 0), 0.0f);
    EXPECT_FLOAT_EQ(A(3, 1), 0.0f);
    EXPECT_FLOAT_EQ(A(3, 2), 0.0f);
    EXPECT_FLOAT_EQ(A(3, 3), 3.0f);

    EXPECT_FLOAT_EQ(b(0), 1.0f);
    EXPECT_FLOAT_EQ(b(1), 1.0f);
    EXPECT_FLOAT_EQ(b(2), 3.0f);
    EXPECT_FLOAT_EQ(b(3), 4.0f);
}