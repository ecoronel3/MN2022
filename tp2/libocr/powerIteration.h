#pragma once
#include <cstdint>
#include <limits>

#include <Eigen/Dense>

namespace mn
{
    std::pair<double, Eigen::VectorXd> powerIteration(const Eigen::MatrixXd& B, const Eigen::VectorXd& x0, uint16_t niter, double epsilon = std::numeric_limits<double>::epsilon());

}