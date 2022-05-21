#include "PCA.h"

#include <Eigen/Dense>

#include "powerIteration.h"
#include "randVector.h"

namespace mn
{
    PCA& PCA::fit(const Eigen::MatrixXd& data)
    {
        const std::uint64_t mFeatures = data.cols();
        const std::uint64_t nSamples = data.rows();
        
        ////// calculate mu = mean ///////
        auto ones = Eigen::VectorXd::Ones(nSamples);
        Eigen::VectorXd mu = data.transpose() * ones;

        // mu *= 1.0 / static_cast<double>(nSamples);
        mu /= static_cast<double>(nSamples);

        ////// calculate covariance matrix ///////
        Eigen::MatrixXd Mx = getCovarianceMatrix(mu, data);

        ////// power method ///////
        m_Components.resize(nComponents, mFeatures);
        for(std::uint16_t i = 0; i < nComponents; ++i)
        {
            Eigen::VectorXd vi = randVectorXd(mFeatures, 0.1, 1.0);
            const auto [eigenValue, eigenVector, iter] = powerIteration(Mx, vi, iteratedPower, toleranceError);
            // deflate
            Mx = Mx - eigenValue*eigenVector*eigenVector.transpose();
            
            m_EigenValues[i] = eigenValue;  
            m_Components.row(i) = eigenVector;
        }
        return *this;
    }

    /// X is an array-like of shape (n_samples, n_features)
    /// returns an array-like of shape (n_samples, n_components)
    Eigen::MatrixXd PCA::transform(const Eigen::MatrixXd& X)
    {
        /// m_Components is an array-like of shape (n_components, n_features)
        return X * m_Components.transpose();
    }

    Eigen::MatrixXd PCA::getCovarianceMatrix(const Eigen::VectorXd& mu, const Eigen::MatrixXd& x)
    {
        const std::uint64_t n = x.rows();
        const double magicNumber = std::sqrt(n - 1.0);

        // X = (X - ones*mu')
        auto ones = Eigen::VectorXd::Ones(n);
        Eigen::MatrixXd X = x - ones * mu.transpose();
        X /= magicNumber;

        // covariance matrix
        // Mx = X'*X
        Eigen::MatrixXd Mx = X.transpose() * X;
        return Mx;
    }
}
