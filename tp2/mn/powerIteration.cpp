#include "powerIteration.h"
#include <iostream>

namespace mn
{
    std::tuple<double, Eigen::VectorXd, uint16_t> powerIteration(const Eigen::MatrixXd& A, const Eigen::VectorXd& x0, const uint16_t niter, const double tol)
    {
        Eigen::VectorXd x{x0};
        for (uint16_t k = 0; k < niter; ++k)
        {
            Eigen::VectorXd y = A * x;
            const auto y_normalized = y.normalized();
            const double err = (x - y_normalized).norm();

            x = y_normalized;

            if (err < tol)
            {
                const double xtAx = x.transpose() * A * x;
                return {xtAx, x, k};
            }
        }
        const double xtAx = x.transpose() * A * x;
        return {xtAx, x, niter};
    }   
}