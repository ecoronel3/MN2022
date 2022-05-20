#pragma once
#include <cstdint>
#include <map>

#include <Eigen/Dense>

namespace mn
{
    class PCA
    {
        public:
            PCA() = default;
            PCA(std::uint16_t components, std::uint16_t iteratedPower_)
                : nComponents(components)
                , iteratedPower(iteratedPower_)
                , m_EigenValues(nComponents)
                , m_Components(nComponents, nComponents)
            {

            }

            PCA& fit(const Eigen::MatrixXd& X);
            PCA& fit(const Eigen::MatrixXd& X, const Eigen::VectorXi& y)
            {
                return fit(X);
            }

            Eigen::MatrixXd transform(const Eigen::MatrixXd& X);

            const Eigen::VectorXd& getEigenValues() const { return m_EigenValues; }
            const Eigen::MatrixXd& getComponents() const { return m_Components; }
            
            uint16_t nComponents{8};
            uint16_t iteratedPower{32};

        private:
            Eigen::MatrixXd getCovarianceMatrix(const Eigen::VectorXd& mu, const Eigen::MatrixXd& x);

            double m_Tolerance{0.0};
            Eigen::VectorXd m_EigenValues;
            Eigen::MatrixXd m_Components;
    };

}
