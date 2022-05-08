#include "powerIteration.h"

namespace mn
{
    std::pair<double, Eigen::VectorXd> powerIteration(const Eigen::MatrixXd& B, const Eigen::VectorXd& x0, const uint16_t niter, const double epsilon)
    {
        Eigen::VectorXd v{x0};
        for (uint16_t i = 0; i < niter; ++i)
        {
            Eigen::VectorXd Bv = B * v;
            const double norm = Bv.norm();
            v = Bv * (1.0 / norm);
        }
        const double vtBv = v.transpose() * B * v;
        const double vtv = v.transpose() * v;
        return {vtBv / vtv, v};
    }
}