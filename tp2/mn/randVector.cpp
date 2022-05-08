#include "randVector.h"
#include <random>

namespace mn
{
    Eigen::VectorXd randVectorXd(std::size_t size, const double min, const double max)
    {
        std::random_device rd;  // Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<double> dist(min, max);

        Eigen::VectorXd v{size};
        for (std::size_t i = 0; i < size; ++i)
        {
            v[i] = dist(gen);
        }
        return v;
    }
    
}