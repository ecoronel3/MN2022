#pragma once
#include <cstdint>

#include <Eigen/Dense>

namespace mn
{
    class PCA
    {
        public:
            PCA(uint16_t components, uint16_t iteratedPower)
                : m_NComponents(components)
                , m_IteratedPower(iteratedPower)
                , m_EigenValues(m_NComponents)
                , m_EigenVectors(m_NComponents, m_NComponents)
            {

            }

            void fit(const Eigen::MatrixXd& x);

            const Eigen::VectorXd& getEigenValues() const { return m_EigenValues; }
            const Eigen::MatrixXd& getEigenVectors() const { return m_EigenVectors; }
            
        protected:
            Eigen::MatrixXd getCovarianceMatrix(const Eigen::VectorXd& mu, const Eigen::MatrixXd& x);
            void deflate(Eigen::MatrixXd& B, const Eigen::VectorXd& eigenVector, const double eigenValue);

        private:
            uint16_t m_NComponents{0};
            uint16_t m_IteratedPower{0};
            double m_Tolerance{0.0};
            Eigen::VectorXd m_EigenValues;
            Eigen::MatrixXd m_EigenVectors;
    };

}
