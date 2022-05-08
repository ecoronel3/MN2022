#pragma once
#include <cstdint>
#include <limits>

#include <Eigen/Dense>

namespace mn
{
    Eigen::VectorXd randVectorXd(std::size_t size, double min = std::numeric_limits<double>::min(), double max = std::numeric_limits<double>::max());
    
}