#include <gtest/gtest.h>

#include <Eigen/Dense>
#include "mn/powerIteration.h"
#include "mn/randVector.h"

namespace 
{
    constexpr double k_Epsilon = 0.000001;
}

TEST(powerIterationTests, DiagonalMatrix)
{
    Eigen::MatrixXd B{{5.0, 0.0, 0.0}, {0.0, 4.0, 0.0}, {0.0, 0.0, 3.0}};
    Eigen::VectorXd x0 = mn::randVectorXd(3, 1.0, 255.0);
    const auto [eigenValue, eigenVector] = mn::powerIteration(B, x0, 100);
    EXPECT_DOUBLE_EQ(eigenValue, 5.0);
    const auto v0 = B*eigenVector;
    const auto v1 = eigenValue*eigenVector;

    EXPECT_NEAR(eigenVector[0], 1.0, k_Epsilon);
    EXPECT_NEAR(eigenVector[1], 0.0, k_Epsilon);
    EXPECT_NEAR(eigenVector[2], 0.0, k_Epsilon);

    EXPECT_NEAR(v0[0], v1[0], k_Epsilon);
    EXPECT_NEAR(v0[1], v1[1], k_Epsilon);
    EXPECT_NEAR(v0[2], v1[2], k_Epsilon);
}
