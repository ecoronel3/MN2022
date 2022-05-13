#include "kNNClassifier.h"

namespace mn
{
    void kNNClassifier::fit(const Eigen::MatrixXd& X, const Eigen::VectorXd& y)
    {
         m_X = X;
         m_y = y;   
    }

    Eigen::VectorXd kNNClassifier::predict(const Eigen::MatrixXd& X)
    {
        Eigen::VectorXd yPredicted(X.rows());
        for (int i = 0; i < X.rows(); i++)
        {   
            priority_queue<pair<double, int>> distances;
            for (int j = 0; j < m_X.rows(); j++)
            {
                distance = (X.row(i) - m_X.row(j)).norm();
                if (distances.size() < m_KNeighbors)
                {
                    distances.push(make_pair(distance, j));
                }
                else if (distances.top().first > distance)
                {
                    distances.pop();    
                    distances.push(make_pair(distance, j));     // replace the greatest distance with the new distance
                }
            }
            map<uint16_t, tuple<int, double>> neighbor_classes;
            uint16_t classification = m_y(distances.top().second);
            int count = 1;

            while (!distances.empty())
            {   
                neighbor = distances.pop();
                neighbor_class = m_y(neighbor.second);
                old_value = neighbor_classes[neighbor_class];
                neighbor_classes[neighbor_class] = make_pair(old_value.first + 1, old_value.second + neighbor.first);

                if(classification == neighbor_class)
                {
                    count++;
                } else if (old_value + 1 > count)
                {
                    classification = neighbor_class;
                    count = old_value + 1;
                }
            }
            yPredicted(i) = classification;
        }
        return yPredicted;
    }
}
