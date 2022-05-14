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
            Eigen::VectorXd predict(const Eigen::MatrixXd& X);

        private:
            uint16_t m_KNeighbors;
            Eigen::MatrixXd m_X;
            Eigen::VectorXd m_y;
    };

}
