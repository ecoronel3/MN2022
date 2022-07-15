from pyexpat import features
import numpy as np
import math
import csv

def func_g(x1, x2):
    return x1**2 + x2

def generate_data(n_samples,):
    mu=0
    sigma=1
    x1 = np.random.uniform(1, 50, n_samples)
    x2 = np.random.uniform(-50, 50, n_samples)
    y = func_g(x1, x2) + np.random.normal(mu, sigma, size=n_samples)
    return [y, x1, x2]

def generate_file(n_samples, filepath):
    features = generate_data(n_samples)

    header = ['id', 'Y']
    for feature_id in range(1, len(features)):
        header.append('X' + str(feature_id))

    data = []
    for sample_id in range(0, n_samples):
        r = [str(sample_id)]
        for feature_id in range(0, len(features)):
            r.append( round(features[feature_id][sample_id], 3) )

        data.append(r)

    with open(filepath, 'w', newline='', encoding='UTF8') as f:
        writer = csv.writer(f, quotechar='"', quoting=csv.QUOTE_NONNUMERIC)
        writer.writerow(header)
        writer.writerows(data)

def main():
    generate_file(150, 'data/synthData2.csv')

if __name__ == '__main__':
    main()