#pragma once
#include <cstdint>

#include <Eigen/Dense>
#include <queues>

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
            VectorXd predict(const Eigen::VectorXd& x);

        private:
            uint16_t m_KNeighbors;
            Eigen::MatrixXd m_X;
            Eigen::VectorXd m_y;
    };

}
