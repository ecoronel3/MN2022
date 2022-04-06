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

TEST(ForwardSubstitutionTest, M33Diagonal)
{
    mn::MatrixNf A = { { 2.0f, 0.0f, 0.0f }, { 0.0f, 4.0f, 0.0f }, { 0.0f, 0.0f, 8.0f} };
    mn::VectorNf b = { 3.0f, 9.0f, 16.0f };
    mn::VectorNf x = { 0.0f, 0.0f, 0.0f };

    mn::ForwardSubstitution(A, b, x);

    EXPECT_FLOAT_EQ(A(0,0), 2.0f);
    EXPECT_FLOAT_EQ(A(0,1), 0.0f);
    EXPECT_FLOAT_EQ(A(0,2), 0.0f);

    EXPECT_FLOAT_EQ(A(1,0), 0.0f);
    EXPECT_FLOAT_EQ(A(1,1), 4.0f);
    EXPECT_FLOAT_EQ(A(1,2), 0.0f);

    EXPECT_FLOAT_EQ(A(2,0), 0.0f);
    EXPECT_FLOAT_EQ(A(2,1), 0.0f);    
    EXPECT_FLOAT_EQ(A(2,2), 8.0f);

    EXPECT_FLOAT_EQ(b(0), 3.0f);
    EXPECT_FLOAT_EQ(b(1), 9.0f);
    EXPECT_FLOAT_EQ(b(2), 16.0f);    

    EXPECT_FLOAT_EQ(x(0), 1.5f);
    EXPECT_FLOAT_EQ(x(1), 2.25f);
    EXPECT_FLOAT_EQ(x(2), 2.0f);
}

TEST(ForwardSusbtitutionTest, M44)
{
    mn::MatrixNf A = {  { 1.0f, 0.0f, 0.0f, 14.0f },
                        { 0.0f, 4.0f, 0.0f, 1.0f },
                        { 0.0f, 0.0f, 4.0f, 1.0f },
                        { 0.0f, 0.0f, 0.0f, 6.0f }, };
    mn::VectorNf b = { 42.0f, 16.0f, 8.0f, 6.0f };
    mn::VectorNf x{ 0.0f, 0.0f, 0.0f, 0.0f };

    mn::ForwardSubstitution(A, b, x);
 
    EXPECT_EQ(x(0), 42);
    EXPECT_EQ(x(1), 4);
    EXPECT_EQ(x(2), 2);
    EXPECT_EQ(x(3), 1);
}