#include <gtest/gtest.h>
#include "ForwardSubstitution.h"

TEST(ForwardSubstitutionTest, M22Identity)
{
    mn::MatrixNf A = { {1.0f, 0.0f }, {0.0f, 1.0f } };
    mn::VectorNf b = { 1.0f, 1.0f };
    mn::VectorNf x{ 0.0f, 0.0f };

    mn::ForwardSubstitution(A, b, x);
    FAIL();
}