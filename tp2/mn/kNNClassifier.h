#pragma once
#include <cstdint>
#include <Eigen/Dense>
#include <functional>

#include "DistanceMetric.h"
#include "Weights.h"

namespace mn
{
    class kNNClassifier
    {
        public:
            kNNClassifier() = default;            
            kNNClassifier(uint16_t kNeighbors_, DistanceMetric distanceMetric_ = DistanceMetric::Euclidean, Weights weights_ = Weights::Distance)
                : kNeighbors(kNeighbors_)
                , distanceMetric(distanceMetric_)
                , weights(weights_)
            {

            }

            kNNClassifier& fit(const Eigen::MatrixXd& X, const Eigen::VectorXi& y);

            Eigen::VectorXi predict(const Eigen::MatrixXd& X);

            float score(const Eigen::MatrixXd& X, const Eigen::VectorXi& y);

            std::uint16_t kNeighbors{5};
            DistanceMetric distanceMetric = DistanceMetric::Euclidean;
            Weights weights = Weights::Distance;

        private:
            using DistanceFunction = std::function<double(const Eigen::MatrixXd&, const Eigen::MatrixXd&)>;

            DistanceFunction getDistanceFunction() const;

        private:
            Eigen::MatrixXd m_X;
            Eigen::VectorXi m_y;
    };

}
