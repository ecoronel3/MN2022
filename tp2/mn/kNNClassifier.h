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

            void fit(const Eigen::MatrixXd& X, const std::vector<uint16_t>& y);
            std::vector<uint16_t> predict(const Eigen::MatrixXd& X);

        private:
            uint16_t m_KNeighbors;
            Eigen::MatrixXd m_X;
            std::vector<uint16_t> m_y;
    };

}
