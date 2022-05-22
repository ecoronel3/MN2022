#include "kNNClassifier.h"
#include <queue>
#include <map>

namespace mn
{
    kNNClassifier& kNNClassifier::fit(const Eigen::MatrixXd& X, const Eigen::VectorXi& y)
    {
         m_X = X;
         m_y = y;
         return *this;
    }

    float kNNClassifier::score(const Eigen::MatrixXd& X, const Eigen::VectorXi& y)
    {
        const auto y_predicted = predict(X);
        const auto n = y.size();
        const auto result = y_predicted - y;
        float sum{0.0f};
        for(auto i = 0; i < n; ++i)
        {
            sum += result(i) == 0 ? 1 : 0;
        }

        return sum / static_cast<float>(n);
    }

    Eigen::VectorXi kNNClassifier::predict(const Eigen::MatrixXd& X)
    {
        auto distanceFun = getDistanceFunction();

        Eigen::VectorXi yPredicted = Eigen::VectorXi::Ones(X.rows());
        for (int i = 0; i < X.rows(); i++)
        {   
            std::priority_queue<std::pair<double, int>> distances;
            for (int j = 0; j < m_X.rows(); j++)
            {
                const double distance = distanceFun(X.row(i), m_X.row(j));
                // if(weights == KNNWeights::Uniform || weights == KNNWeights::Distance)
                // {
                //     distance = (X.row(i) - m_X.row(j)).norm();
                // } else
                // {
                //     distance = (X.row(i) - m_X.row(j)).lpNorm<1>();
                // }

                if (distances.size() < kNeighbors)
                {
                    distances.push(std::make_pair(distance, j));
                }
                else if (distances.top().first > distance)
                {
                    distances.pop();    
                    distances.push(std::make_pair(distance, j));     // replace the greatest distance with the new distance
                }
            }

            std::map<int, double> neighbor_classes;
            int classification = -1;        
            double max_count = 0.0;
            while (!distances.empty())
            {   
                auto neighbor = distances.top();
                distances.pop();
                auto neighbor_class = m_y[neighbor.second];
                double old_value = 0.0;
                if(neighbor_classes.count(neighbor_class) > 0)
                {
                    old_value = neighbor_classes[neighbor_class];
                }
                
                double new_value;
                new_value = old_value + 1.0/neighbor.first;

                if(weights == Weights::Distance)
                {
                    new_value = old_value + 1.0/neighbor.first;
                } 
                else 
                {
                    new_value = old_value + 1.0;
                }

                if(classification == neighbor_class)
                {
                    max_count = new_value;
                } 
                else if (new_value >= max_count)  
                // Como voy sacando en orden decreciente de distancia, conviene que gane el ultimo en ser sacado de la cola
                {
                    classification = neighbor_class;
                    max_count = new_value;
                }
                neighbor_classes[neighbor_class] = new_value;

            }
            yPredicted(i) = classification;
        }
        return yPredicted;
    }

    kNNClassifier::DistanceFunction kNNClassifier::getDistanceFunction() const
    {
        if (distanceMetric == DistanceMetric::Euclidean)
        {
            return [](const Eigen::MatrixXd& X, const Eigen::MatrixXd& Y)
            {
                return (X - Y).norm();
            };
        }
        else if (distanceMetric == DistanceMetric::Manhattan)
        {
            return [](const Eigen::MatrixXd& X, const Eigen::MatrixXd& Y)
            {
                return (X - Y).lpNorm<1>();
            };
        }
        else
        {
            return [](const Eigen::MatrixXd& X, const Eigen::MatrixXd& Y)
            {
                return (X - Y).lpNorm<Eigen::Infinity>();
            };
        }
    }
}
