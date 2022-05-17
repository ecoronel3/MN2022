#include "kNNClassifier.h"
#include <queue>
#include <map>

namespace mn
{
    void kNNClassifier::fit(const Eigen::MatrixXd& X, const std::vector<uint16_t>& y)
    {
         m_X = X;
         m_y = y;
         int n = y.size();
         int max = -1;
         
    }

    std::vector<uint16_t> kNNClassifier::predict(const Eigen::MatrixXd& X)
    {
        std::vector<uint16_t> yPredicted(X.rows(), -1);
        for (int i = 0; i < X.rows(); i++)
        {   
            std::priority_queue<std::pair<double, int>> distances;
            for (int j = 0; j < m_X.rows(); j++)
            {
                auto distance = (X.row(i) - m_X.row(j)).norm();
                if (distances.size() < m_KNeighbors)
                {
                    distances.push(std::make_pair(distance, j));
                }
                else if (distances.top().first > distance)
                {
                    distances.pop();    
                    distances.push(std::make_pair(distance, j));     // replace the greatest distance with the new distance
                }
            }
            std::map<std::uint16_t, std::pair<int, double>> neighbor_classes; //par cantidad, distancia total
            uint16_t classification = -1;
            int count = 0;

            while (!distances.empty())
            {   
                auto neighbor = distances.top();
                distances.pop();
                auto neighbor_class = m_y[neighbor.second];
                auto old_value = neighbor_classes[neighbor_class];
                neighbor_classes[neighbor_class] = std::make_pair(old_value.first + 1, old_value.second + neighbor.first);

                if(classification == neighbor_class)
                {
                    count++;
                } 
                else if (old_value.first + 1 >= count)  
                // Como voy sacando en orden decreciente de distancia, conviene que gane el ultimo en ser sacado de la cola
                {
                    classification = neighbor_class;
                    count = old_value.first + 1;
                }
            }
            yPredicted[i] = classification;
        }
        return yPredicted;
    }
}
