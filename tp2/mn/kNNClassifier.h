#pragma once
#include <cstdint>

#include <Eigen/Dense>

namespace mn
{
    class kNNClassifier
    {
        public:
            kNNClassifier() = default;            
            kNNClassifier(uint16_t kNeighbors_)
                : kNeighbors(kNeighbors_)
            {

            }

            void fit(const Eigen::MatrixXd& X, const std::vector<uint16_t>& y);
            std::vector<uint16_t> predict(const Eigen::MatrixXd& X);

            float score(const Eigen::MatrixXd& X, const Eigen::VectorXd& y);

            uint16_t kNeighbors{5};

        private:            
            Eigen::MatrixXd m_X;
            std::vector<uint16_t> m_y;
    };

}
