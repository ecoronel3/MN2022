import sys
sys.path.append('build\Debug')

import mnpy as mn
import numpy as np

B = np.array([ [5, 0, 0], [0, 4, 0], [0, 0, 3]])
x0 = np.array([1, 1, 1])
eigenvalue = mn.powerIteration(B, x0, 120, 0.0001)
print(eigenvalue)

training_dataset = np.array([ [1.0, 0.0, 0.0], [0.0, 1.0, 0.0], [0.0, 0.0, 1.0], [1.0, 1.0, 1.0]])
targets_dataset = np.array([0, 1, 0, 4 ])

pca = mn.PCA(3, 64)
pca.fit(training_dataset)
knn = mn.kNNClassifier(1)
knn.fit(pca.transform(training_dataset), targets_dataset)

data = np.array([ [1.0, 0.0, 0.0], [0.0, 1.0, 0.0]])
y = knn.predict(pca.transform(data))
print(y)
## y = [0, 1]


## print(pca.getEigenVectors())


# knn.fit()



