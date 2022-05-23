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
    const auto [eigenValue, eigenVector, iter] = mn::powerIteration(B, x0, 100, 0.00000001);
    EXPECT_DOUBLE_EQ(eigenValue, 5.0);
    const auto v0 = B*eigenVector;
    const auto v1 = eigenValue*eigenVector;

    EXPECT_NEAR(eigenVector[0], 1.0, k_Epsilon);
    EXPECT_NEAR(eigenVector[1], 0.0, k_Epsilon);
    EXPECT_NEAR(eigenVector[2], 0.0, k_Epsilon);

    EXPECT_NEAR(v0[0], v1[0], k_Epsilon);
    EXPECT_NEAR(v0[1], v1[1], k_Epsilon);
    EXPECT_NEAR(v0[2], v1[2], k_Epsilon);
    
    std::cout << iter << std::endl;
}

TEST(powerIterationTests, SymmetricMatrix)
{
    Eigen::MatrixXd A{{1.0, -1.0, 0.0}, {-2.0, 4.0, -2.0}, {0.0, -1.0, 1.0}};
    Eigen::VectorXd x0 = mn::randVectorXd(3, 1.0, 255.0);
    const auto [eigenValue, eigenVector, iter] = mn::powerIteration(A, x0, 1000, 0.0000001);
    EXPECT_DOUBLE_EQ(eigenValue, 5.0);
    
    const auto v0 = A*eigenVector;
    const auto v1 = eigenValue*eigenVector;

    // x_1 = x_3; x_2 = -4 x_3 (real number)
    EXPECT_NEAR(abs(eigenVector[0]), 1.0/sqrt(18), k_Epsilon);
    EXPECT_NEAR(abs(eigenVector[1]), 4.0/sqrt(18), k_Epsilon);
    EXPECT_NEAR(abs(eigenVector[2]), 1.0/sqrt(18), k_Epsilon);
    
    EXPECT_NEAR(v0[0], v1[0], k_Epsilon);
    EXPECT_NEAR(v0[1], v1[1], k_Epsilon);
    EXPECT_NEAR(v0[2], v1[2], k_Epsilon);

    std::cout << iter << std::endl;
}

TEST(powerIterationTests, MatrizSinPropiedadesAparentes)
{
    Eigen::MatrixXd A{{7.0, 2.0, 3.0}, {0.0, 2.0, 0.0}, {-6.0, -2.0, -2.0}};
    Eigen::VectorXd x0 = mn::randVectorXd(3, 1.0, 255.0);
    const auto [eigenValue, eigenVector, iter] = mn::powerIteration(A, x0, 512, 0.00000001);
    EXPECT_NEAR(eigenValue, 4,  0.001);
    
    const auto v0 = A*eigenVector;
    const auto v1 = eigenValue*eigenVector;

    EXPECT_NEAR(eigenVector[0], 1.0/sqrt(2), k_Epsilon);
    EXPECT_NEAR(eigenVector[1], 0.0, k_Epsilon);
    EXPECT_NEAR(eigenVector[2], -1.0/sqrt(2), k_Epsilon);
    
    EXPECT_NEAR(v0[0], v1[0], k_Epsilon);
    EXPECT_NEAR(v0[1], v1[1], k_Epsilon);
    EXPECT_NEAR(v0[2], v1[2], k_Epsilon);

    std::cout << iter << std::endl;
}

TEST(powerIterationTests, TriangularMatrix)
{
    Eigen::MatrixXd A{{1.0, 0.0, 1.0}, {0.0, 1.0, 1.0}, {0.0, 0.0, 2.0}};
    Eigen::VectorXd x0 = mn::randVectorXd(3, 1.0, 255.0);
    const auto [eigenValue, eigenVector, iter] = mn::powerIteration(A, x0, 1000, 0.00000001);
    EXPECT_NEAR(eigenValue, 2, 0.001);
    
    const auto v0 = A*eigenVector;
    const auto v1 = eigenValue*eigenVector;

    EXPECT_NEAR(eigenVector[0], 2.0/sqrt(12), k_Epsilon);
    EXPECT_NEAR(eigenVector[1], 2.0/sqrt(12), k_Epsilon);
    EXPECT_NEAR(eigenVector[2], 2.0/sqrt(12), k_Epsilon);
    
    EXPECT_NEAR(v0[0], v1[0], k_Epsilon);
    EXPECT_NEAR(v0[1], v1[1], k_Epsilon);
    EXPECT_NEAR(v0[2], v1[2], k_Epsilon);

    std::cout << iter << std::endl;
}