#include <gtest/gtest.h>

#include <Eigen/Dense>
#include "mn/kNNClassifier.h"

TEST(kNNClassifier, k1)
{
    mn::kNNClassifier knn{1};

    Eigen::MatrixXd data{{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}};
    Eigen::VectorXi labels{3};
    labels << 0, 1, 2;
    knn.fit(data, labels);
    auto classification = knn.predict(data);
    EXPECT_EQ(classification.size(), 3);
    for(int i = 0; i < 3; i++)
    {
        EXPECT_EQ(classification[i], labels[i]);
    }
}

TEST(kNNClassifier, kn)
{
    mn::kNNClassifier knn{3, mn::DistanceMetric::Euclidean, mn::Weights::Uniform};

    Eigen::MatrixXd data{{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}};
    Eigen::VectorXi labels{3};
    labels << 0, 1, 1;
    knn.fit(data, labels);
    auto classification = knn.predict(data);
    EXPECT_EQ(classification.size(), 3);
    for(int i = 0; i < 3; i++)
    {
        EXPECT_EQ(classification[i], 1);
    }
}

TEST(kNNClassifier, kn2)
{
    mn::kNNClassifier knn{2};

    Eigen::MatrixXd trainData{{1.0, 0.0, 0.0}, {2.0, 0.0, 0.0}, {0.0, 0.0, 2.0}, {0.0, 0.0, 3.0}};
    Eigen::VectorXi labels{4};
    labels << 0 , 0 , 1 , 1;
    Eigen::MatrixXd data{{1.5, 0.0, 0.0}, {0.0, 0.0, 2.5}};
    knn.fit(trainData, labels);
    auto classification = knn.predict(data);
    EXPECT_EQ(classification.size(), 2);
    EXPECT_EQ(classification[0], 0);
    EXPECT_EQ(classification[1], 1);
    
}

TEST(kNNClassifier, kn3)
{
    mn::kNNClassifier knn{3};

    Eigen::MatrixXd trainData{{0.0, 0.0, -2.0}, {0.0, 0.0, -3.0}, {0.0, 0.0, 2.0}, {0.0, 0.0, 3.0}};
    Eigen::VectorXi labels{4};
    labels << 0,0,1,1;
    Eigen::MatrixXd data{{0.0, 0.0, -2.5}, {0.0, 0.0, 2.5}};
    knn.fit(trainData, labels);
    auto classification = knn.predict(data);
    EXPECT_EQ(classification.size(), 2);
    EXPECT_EQ(classification[0], 0);
    EXPECT_EQ(classification[1], 1);
    
}

TEST(kNNClassifier, knEmpate)
{
    mn::kNNClassifier knn{4};

    Eigen::MatrixXd trainData{{0.0, 0.0, -2.0}, {0.0, 0.0, -3.0}, {0.0, 0.0, 2.0}, {0.0, 0.0, 3.0}};
    Eigen::VectorXi labels{4};
    labels << 0,0,1,1;
    Eigen::MatrixXd data{{0.0, 0.0, -2.5}, {0.0, 0.0, 2.5}};
    knn.fit(trainData, labels);
    auto classification = knn.predict(data);
    EXPECT_EQ(classification.size(), 2);
    EXPECT_EQ(classification[0], 0);
    EXPECT_EQ(classification[1], 1);
    
}

TEST(kNNClassifier, knWeighted)
{
    mn::kNNClassifier knn{5, mn::DistanceMetric::Euclidean};

    Eigen::MatrixXd trainData{{0.0, 0.0, -2.0}, {0.0, 0.0, -3.0}, {0.0, 0.0, 1000.0}, {0.0, 0.0, 3000.0}, {0.0, 0.0, 2000.0}};
    Eigen::VectorXi labels{5};
    labels << 0,0,1,1,1;
    Eigen::MatrixXd data{{0.0, 0.0, -2.5}};
    knn.fit(trainData, labels);
    auto classification = knn.predict(data);
    EXPECT_EQ(classification.size(), 1);
    EXPECT_EQ(classification[0], 0);
    
}

TEST(kNNClassifier, knManhattan)
{
    mn::kNNClassifier knn{4, mn::DistanceMetric::Manhattan};

    Eigen::MatrixXd trainData{{0.0, 0.0, -2.0}, {0.0, 0.0, -3.0}, {0.0, 0.0, 2.0}, {0.0, 0.0, 3.0}};
    Eigen::VectorXi labels{4};
    labels << 0,0,1,1;
    Eigen::MatrixXd data{{0.0, 0.0, -2.5}, {0.0, 0.0, 2.5}};
    knn.fit(trainData, labels);
    auto classification = knn.predict(data);
    EXPECT_EQ(classification.size(), 2);
    EXPECT_EQ(classification[0], 0);
    EXPECT_EQ(classification[1], 1);
    
}