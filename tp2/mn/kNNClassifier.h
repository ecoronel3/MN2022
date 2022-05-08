#pragma once
#include <cstdint>

#include <Eigen/Dense>

namespace mn
{
    class kNNClassifier
    {
        public:
            kNNClassifier(uint16_t kNeighbors)
                : m_KNeighbors(kNeighbors)
            {

            }

            void fit(const Eigen::MatrixXd& X, const Eigen::VectorXd& y);
            uint16_t predict(const Eigen::VectorXd& x);

        private:
            uint16_t m_KNeighbors;
    };

}
