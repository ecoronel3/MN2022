#pragma once
#include <cstdint>
#include <map>

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

            kNNClassifier& fit(const Eigen::MatrixXd& X, const Eigen::VectorXi& y);

            Eigen::VectorXi predict(const Eigen::MatrixXd& X);

            float score(const Eigen::MatrixXd& X, const Eigen::VectorXi& y);

            std::uint16_t kNeighbors{5};

        private:            
            Eigen::MatrixXd m_X;
            Eigen::VectorXi m_y;
    };

}
