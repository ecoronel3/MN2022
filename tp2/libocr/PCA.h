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
            {

            }

            void fit(const Eigen::MatrixXd& x);
        
        private:
            uint16_t m_NComponents{0};
            uint16_t m_IteratedPower{0};
            double m_Tolerance{0.0};
            Eigen::VectorXd m_SingularValues;
    };

}
