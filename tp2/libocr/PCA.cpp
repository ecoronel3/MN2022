#include "PCA.h"

#include <Eigen/Dense>

#include "powerIteration.h"
#include "randVector.h"


namespace mn
{
    void PCA::fit(const Eigen::MatrixXd& data)
    {
        const std::uint64_t m = data.cols();
        const std::uint64_t n = data.rows();
        ////// calculate mu = mean ///////                
        
        auto ones = Eigen::VectorXd::Ones(n);
        Eigen::VectorXd mu = data.transpose() * ones;

        mu *= 1.0 / static_cast<double>(n);

        ////// calculate covariance matrix ///////
        Eigen::MatrixXd covMat = getCovarianceMatrix(mu, data);

        ////// power method ///////
        m_EigenVectors.resize(m_NComponents, m);
        for(std::uint16_t i = 0; i < m_NComponents; ++i)
        {
            Eigen::VectorXd vi = randVectorXd(m, 0.1, 1.0);
            const auto [eigenValue, eigenVector] = powerIteration(covMat, vi, m_IteratedPower);
            // deflate
            covMat = covMat - eigenValue*eigenVector*eigenVector.transpose();
            
            m_EigenValues[i] = eigenValue;
            m_EigenVectors.row(i) = eigenVector;
            // xt::blas::ger(v, v, B, xt::xscalar<double>(-1.0*lambda));   

            // covMat = covMat - eigenValue*vi
        }
    }

    Eigen::MatrixXd PCA::getCovarianceMatrix(const Eigen::VectorXd& mu, const Eigen::MatrixXd& x)
    {
        const std::uint64_t m = x.cols();
        const std::uint64_t n = x.rows();
        double magicNumber = std::sqrt(n - 1.0);

        // X = (X - ones*mu')
        auto ones = Eigen::VectorXd::Ones(x.rows());
        Eigen::MatrixXd X = x - ones * mu.transpose();
        X *= (1.0 / magicNumber);

        // covariance matrix
        // covMat = X'*X
        Eigen::MatrixXd covMat = X.transpose() * X;
        return covMat;
    }
}
