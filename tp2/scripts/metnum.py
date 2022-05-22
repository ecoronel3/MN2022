import sys
from unittest import result
sys.path.append('..\install\lib')
import mnpy as mn

from matplotlib import pyplot
from itertools import product
import sklearn.model_selection as sk_model_selection
from joblib import Parallel

class NewGridSearchCV:
    def __init__(self, pca_parameters, knn_parameters, cv, n_jobs=None, pre_dispatch="2*n_jobs"):
        self.pca_parameters = pca_parameters
        self.knn_parameters = knn_parameters
        self.cv = cv
        self.n_jobs = n_jobs
        self.pre_dispatch = pre_dispatch

    def fit(self, X, y):
        self.results = []
        self.best_params = { 'mean_score': 0 }

        # parallel = Parallel(n_jobs=self.n_jobs, pre_dispatch=self.pre_dispatch)

        knn_params = sk_model_selection.ParameterGrid(self.knn_parameters)
        pca_params = sk_model_selection.ParameterGrid(self.pca_parameters)

        for ( (pca_idx, pca_cand), (knn_idx, knn_cand)), (idx, (train, test)) in product( product( enumerate(pca_params), enumerate(knn_params)), enumerate(self.cv.split(X, y))):

            result = { 'pca_parameters': pca_cand, 'knn_parameters': knn_cand, 'split': idx }

            X_train = X[train]
            y_train = y[train]
            X_test = X[test]
            y_test = y[test]

            # Setup transformer
            pca = mn.PCA()
            if 'n_component' in pca_cand:
                pca.n_component = pca_cand['n_component']
            
            if 'iterated_power' in pca_cand:
                pca.iterated_power = pca_cand['iterated_power']
            
            if 'tolerance_error' in pca_cand:
                pca.tolerance_error = pca_cand['tolerance_error']

            pca.fit(X_train, y_train)
            X_traing_transformed = pca.transform(X_train)

            # Setup scorer
            knn = mn.kNNClassifier()
            if 'k_neighbor' in knn_cand:
                knn.k_neighbor = knn_cand['k_neighbor']

            if 'weights' in knn_cand:
                knn.weights = knn_cand['weights']

            knn.fit(X_traing_transformed, y_train)
            X_test_transformed = pca.transform(X_test)
            score =  knn.score(X_test_transformed, y_test)
            result['score'] = score
            self.results.append(result)
        
        return self




            
class GridSearchCV:
    def __init__(self, n_components, iterated_powers, tolerance_errors, k_neighbors, cv):
        self.n_components = n_components
        self.iterated_powers = iterated_powers
        self.tolerance_errors = tolerance_errors
        self.k_neighbors = k_neighbors
        self.cv = cv

    def fit(self, X, y):
        self.results = []
        self.best_params = {
            'mean_score': 0
        }

        for n_component in self.n_components:
            for iterated_power in self.iterated_powers:
                for tolerance_error in self.tolerance_errors:
                    for k_neighbor in self.k_neighbors:
                        n_splits = self.cv.get_n_splits(X, y)
                        total_score = 0.0
                        for k, (train, test) in enumerate(self.cv.split(X, y)):
                            pca = mn.PCA(n_component, iterated_power)
                            pca.tolerance_error = tolerance_error
                            X_train = X[train]
                            y_train = y[train]
                            pca.fit(X_train, y_train)
                            X_traing_transformed = pca.transform(X[train])

                            knn = mn.kNNClassifier(k_neighbor, mn.KNNWeights.Uniform)
                            knn.fit(X_traing_transformed, y_train)
                            X_test = pca.transform(X[test])
                            y_test = y[test]
                            score =  knn.score(X_test, y_test)
                            total_score += score

                        mean_score = total_score / n_splits

                        result = { 
                                'n_component': n_component, 
                                'iterated_power': iterated_power,
                                'k_neighbor': k_neighbor,
                                'mean_score': mean_score
                            }

                        if self.best_params['mean_score'] < result['mean_score']:
                            self.best_params = result

                        self.results.append(result)

        return self

def plot_gallery(images, titles, h, w, n_row=1, n_col=2):
    pyplot.figure(figsize=(1.8 * n_col, 2.4 * n_row))
    pyplot.subplots_adjust(bottom=0, left=.01, right=.99, top=.90, hspace=.35)
    for i in range(n_row * n_col):
        pyplot.subplot(n_row, n_col, i + 1)
        pyplot.imshow(images[i].reshape((h, w)), cmap=pyplot.cm.gray)
        pyplot.title(titles[i], size=12)
        pyplot.xticks(())
        pyplot.yticks(())
