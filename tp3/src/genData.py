from pyexpat import features
import numpy as np
import math
import csv

def generate_data(n_samples, m_features):    
    features = []
    mu=0
    sigma=1
    X = [x for x in range(1, n_samples + 1) ]    
    for feature_generator in m_features:
        feature_values = np.array(list(map(feature_generator, X)))
        feature_values = feature_values + np.random.normal(mu, sigma, size=n_samples)
        features.append(feature_values)

    return features

def generate_file(n_samples, m_features, filepath):
    features = generate_data(n_samples, m_features)

    header = ['id', 'X']    
    for feature_id in range(1, len(m_features) + 1):
        header.append('feature_' + str(feature_id))

    data = []
    for sample_id in range(0, n_samples):
        r = [str(sample_id), sample_id]
        for feature_id in range(0, len(m_features)):
            r.append( round(features[feature_id][sample_id], 3) )

        data.append(r)

    with open(filepath, 'w', newline='', encoding='UTF8') as f:
        writer = csv.writer(f, quotechar='"', quoting=csv.QUOTE_NONNUMERIC)
        writer.writerow(header)
        writer.writerows(data)

def main():
    functors = [
            lambda x: 0.2*x,
            lambda x: 4.0*math.sin(math.pi * x/64),
            lambda x: math.sqrt(x)*0.5
            ]

    generate_file(150, functors, 'data/synthData.csv')

if __name__ == '__main__':
    main()