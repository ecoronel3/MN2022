#include <gtest/gtest.h>

#include <Eigen/Dense>
#include "libocr/PCA.h"

TEST(PCATests, Constructor)
{
    mn::PCA pca{3, 50};

    Eigen::MatrixXd m{{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}};
    pca.fit(m);

}
