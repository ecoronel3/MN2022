#include <gtest/gtest.h>

#include <Eigen/Dense>
#include "libocr/PCA.h"

TEST(PCATests, SquareMatrix)
{
    mn::PCA pca{3, 120};

    Eigen::MatrixXd data{{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}};
    pca.fit(data);
    EXPECT_EQ(pca.getEigenValues().size(), 3);
    EXPECT_EQ(pca.getEigenVectors().cols(), 3);
    EXPECT_EQ(pca.getEigenVectors().rows(), 3);

}

TEST(PCATests, NonSquareMatrix)
{
    mn::PCA pca{3, 64};

    Eigen::MatrixXd data{{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 1.0, 1.0}};
    pca.fit(data);

    EXPECT_EQ(pca.getEigenValues().size(), 3);    
    EXPECT_EQ(pca.getEigenVectors().rows(), 3);
    EXPECT_EQ(pca.getEigenVectors().cols(), 3);
}

TEST(PCATests, NonSquareMatrix4)
{
    mn::PCA pca{5, 64};

    Eigen::MatrixXd data{
        {0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0}, 
        {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0}, 
        {0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, 
        {0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0}, 
        {1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, 
        {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0}, 
        {0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0}, 
        {1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0}
    };
    pca.fit(data);

    EXPECT_EQ(pca.getEigenValues().size(), 5);
    EXPECT_EQ(pca.getEigenVectors().rows(), 5);
    EXPECT_EQ(pca.getEigenVectors().cols(), 16);
}
