#pragma once
#include <cstdint>
#include <map>

#include <Eigen/Dense>

namespace mn
{
    enum class KNNWeights
    {
        Uniform,
        Distance,
        Custom
    };

    class kNNClassifier
    {
        public:
            kNNClassifier() = default;            
            kNNClassifier(uint16_t kNeighbors_, KNNWeights weights_ = KNNWeights::Uniform)
                : kNeighbors(kNeighbors_)
                , weights(weights_)
            {
                
            }

            kNNClassifier& fit(const Eigen::MatrixXd& X, const Eigen::VectorXi& y);

            Eigen::VectorXi predict(const Eigen::MatrixXd& X);

            float score(const Eigen::MatrixXd& X, const Eigen::VectorXi& y);

            std::uint16_t kNeighbors{5};
            KNNWeights weights = KNNWeights::Uniform;

        private:            
            Eigen::MatrixXd m_X;
            Eigen::VectorXi m_y;
    };

}
