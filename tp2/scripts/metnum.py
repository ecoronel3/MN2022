import sys
sys.path.append('..\install\lib')
import mnpy as mn

from matplotlib import pyplot


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
            'score': 0
        }

        for k, (train, test) in enumerate(self.cv.split(X, y)):
            for n_component in self.n_components:
                for iterated_power in self.iterated_powers:
                    for tolerance_error in self.tolerance_errors:
                        for k_neighbor in self.k_neighbors:

                            result = { 
                                'n_component': n_component, 
                                'iterated_power': iterated_power,
                                'k_neighbor': k_neighbor,
                                'cv_split': k
                            }

                            pca = mn.PCA(n_component, iterated_power)
                            pca.tolerance_error = tolerance_error
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

def plot_gallery(images, titles, h, w, n_row=1, n_col=2):
    pyplot.figure(figsize=(1.8 * n_col, 2.4 * n_row))
    pyplot.subplots_adjust(bottom=0, left=.01, right=.99, top=.90, hspace=.35)
    for i in range(n_row * n_col):
        pyplot.subplot(n_row, n_col, i + 1)
        pyplot.imshow(images[i].reshape((h, w)), cmap=pyplot.cm.gray)
        pyplot.title(titles[i], size=12)
        pyplot.xticks(())
        pyplot.yticks(())

def graph_config(legends, results):
    old_n_neighbors = legends[0]['knn__n_neighbors']
    set_of_lists_with_results = []
    list_with_results = []
    graph_names = []
    for index, legend in enumerate(legends):
        new_n_neighbors = legend['knn__n_neighbors']

        if new_n_neighbors == old_n_neighbors:
            list_with_results.append(results[index])
        else:
            graph_names.append(old_n_neighbors)
            set_of_lists_with_results.append(list_with_results)
            list_with_results = [results[index]]
            old_n_neighbors = new_n_neighbors
    graph_names.append(new_n_neighbors)
    set_of_lists_with_results.append(list_with_results)
    return graph_names, set_of_lists_with_results

def graph(N_COMPONENTS, graph_names, set_of_lists_with_results):
    traces = []
    for index, set in enumerate(set_of_lists_with_results):
        x = N_COMPONENTS
        y = set
        name = "cantidad de vecinos = " + str(graph_names[index])
        traces.append(Scatter(x=x, y=y, name=name))
    layout = Layout(
        xaxis=dict(
            title='Cantidad de componentes principales',
            type='log',
            autorange=True
        ),
        yaxis=dict(
            title='% Accuracy',
            type='log',
            autorange=True
        ),
        title="Medida de performance - Accuracy"
    )
    figure = Figure(data=traces, layout=layout)
    plotly.offline.iplot(figure)
