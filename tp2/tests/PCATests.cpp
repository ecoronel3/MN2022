#include <gtest/gtest.h>

#include <Eigen/Dense>
#include "mn/PCA.h"

TEST(PCATests, FitSquareMatrix)
{
    mn::PCA pca{3, 120};

    Eigen::MatrixXd data{{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}};
    pca.fit(data);
    EXPECT_EQ(pca.getEigenValues().size(), 3);
    EXPECT_EQ(pca.getEigenVectors().cols(), 3);
    EXPECT_EQ(pca.getEigenVectors().rows(), 3);

}

TEST(PCATests, FitNonSquareMatrix)
{
    mn::PCA pca{3, 64};

    Eigen::MatrixXd data{{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 1.0, 1.0}};
    pca.fit(data);

    EXPECT_EQ(pca.getEigenValues().size(), 3);    
    EXPECT_EQ(pca.getEigenVectors().rows(), 3);
    EXPECT_EQ(pca.getEigenVectors().cols(), 3);
}

TEST(PCATests, FitNonSquareMatrix4)
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


TEST(PCATests, Transform)
{
    mn::PCA pca{5, 64};

    Eigen::MatrixXd data{
        {0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0}, 
        {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0}, 
        {0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, 
        {0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.5, 1.0, 1.0}, 
        {1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, 
        {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0}, 
        {0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0}, 
        {1.0, 0.5, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0}
    };
    pca.fit(data);
    Eigen::MatrixXd X{  {0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0} };

    Eigen::MatrixXd Y = pca.transform(X);

    EXPECT_EQ(Y.rows(), 5);
    EXPECT_EQ(Y.cols(), 16);

}
