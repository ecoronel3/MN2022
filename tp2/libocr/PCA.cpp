#include "PCA.h"

#include <Eigen/Dense>

namespace mn
{
    void PCA::fit(const Eigen::MatrixXd& x)
    {
        ////// calculate mu ///////                
        auto ones = Eigen::VectorXd::Ones(x.rows());
        Eigen::VectorXd mu = x.transpose() * ones;
        const double n = static_cast<double>(x.rows());
        mu = mu * 1.0 / n;

        ////// calculate covariance matrix ///////
        ////// power method ///////

    }
}
