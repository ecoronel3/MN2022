import sys
sys.path.append('build\Debug')

import mnpy as mn
import numpy as np

B = np.array([ [5, 0, 0], [0, 4, 0], [0, 0, 3]])
x0 = np.array([1, 1, 1])
eigenvalue = mn.powerIteration(B, x0, 120, 0.0001)
print(eigenvalue)

data = np.array([ [1.0, 0.0, 0.0], [0.0, 1.0, 0.0], [0.0, 0.0, 1.0], [1.0, 1.0, 1.0]])
pca = mn.PCA(3, 64)
pca.fit(data)
print(pca.getEigenVectors())

knn = mn.kNNClassifier(3)
# knn.fit()
