#pragma once
#include <cstdint>

#include <Eigen/Dense>

namespace mn
{
    class PCA
    {
        public:
            PCA(std::uint16_t components, std::uint16_t iteratedPower)
                : m_NComponents(components)
                , m_IteratedPower(iteratedPower)
                , m_EigenValues(m_NComponents)
                , m_Components(m_NComponents, m_NComponents)
            {

            }

            void fit(const Eigen::MatrixXd& x);
            Eigen::MatrixXd transform(const Eigen::MatrixXd& X);

            const Eigen::VectorXd& getEigenValues() const { return m_EigenValues; }
            const Eigen::MatrixXd& getComponents() const { return m_Components; }
            
        private:
            Eigen::MatrixXd getCovarianceMatrix(const Eigen::VectorXd& mu, const Eigen::MatrixXd& x);

            uint16_t m_NComponents{0};
            uint16_t m_IteratedPower{0};
            double m_Tolerance{0.0};
            Eigen::VectorXd m_EigenValues;
            Eigen::MatrixXd m_Components;
    };

}
