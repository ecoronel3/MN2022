import sys

sys.path.append('..\install\lib')

import mnpy as mn

class GridSearchCV:
    def __init__(self, n_components, iterated_powers, k_neighbors, cv):
        self.n_components = n_components
        self.iterated_powers = iterated_powers
        self.k_neighbors = k_neighbors
        self.cv = cv

    def fit(self, X, y):
        self.results = []
        self.best_params = {
            'score': 0
        }

        for k, (train, test) in enumerate(self.cv.split(X, y)):
            for n_component in self.n_components:
                for iterated_power in self.iterated_powers:
                    for k_neighbor in self.k_neighbors:

                        result = { 
                            'n_component': n_component, 
                            'iterated_power': iterated_power,
                            'k_neighbor': k_neighbor,
                            'cv_split': k
                        }

                        pca = mn.PCA(n_component, iterated_power)
                        X_train = X[train]
                        y_train = y[train]
                        pca.fit(X_train, y_train)
                        X_traing_transformed = pca.transform(X[train])

                        knn = mn.kNNClassifier(k_neighbor)
                        knn.fit(X_traing_transformed, y_train)
                        X_test = pca.transform(X[test])
                        y_test = y[test]
                        result['score'] =  knn.score(X_test, y_test)
                        if self.best_params['score'] < result['score']:
                            self.best_params = result

                        self.results.append(result)

        return self
