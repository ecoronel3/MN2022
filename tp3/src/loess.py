import numpy as np
import math
import numpy.linalg as linalg
import pandas as pd
import sklearn as skl
from sklearn.preprocessing import PolynomialFeatures
from sklearn.base import BaseEstimator
import heapq

def tricubic(x):
    y = np.zeros_like(x)
    idx = (x >= -1) & (x <= 1)
    y[idx] = np.power(1.0 - np.power(np.abs(x[idx]), 3), 3)
    return y

def bisquare(x):
    y = np.zeros_like(x)
    idx = (x >= -1) & (x <= 1)
    y[idx] = np.power(1.0 - np.power(x[idx], 2), 2)
    return y

def _normalize(array, est):
    stds = array.std(axis=0)    
    return (array - array.mean(axis=0))/stds, (est - array.mean(axis=0))/stds

def _tricubic_weights(distances, max_dist):
    weights = tricubic(distances/max_dist)
    return np.diag(weights)

def _bisquare_weights(distances, max_dist):
    weights = bisquare(distances/max_dist)
    return np.diag(weights)

class Loess(BaseEstimator):
    def __init__(self, f=0.5, degree=2, dist=2, weight='tricubic', normalize=True) -> None:
        self.f = f
        self.degree = degree
        self.dist = dist
        self.weight = weight
        self.normalize = normalize

    def fit(self, X, y):
        self.q = int(math.ceil(self.f*len(y)))
        self.X = X
        self.y = y
        self.get_weights = _tricubic_weights if self.weight=='tricubic' else _bisquare_weights

        return self

    def predict(self, to_estimate):
        poly = PolynomialFeatures(degree=self.degree)
        cant = len(to_estimate)
        y_ests = np.zeros(cant,dtype="float64")

        X = self.X
        if self.normalize:
            X, to_estimate = _normalize(X, to_estimate)

        for i in range(cant):
            distances = linalg.norm(X - to_estimate[i], ord=self.dist, axis=1)
            indexes, max_dist = self.get_indexes(distances, self.q)

            A = poly.fit_transform(X[indexes])
            x = poly.transform(to_estimate[i].reshape(1,-1))

            W = self.get_weights(distances[indexes], max_dist)

            b = self.y[indexes]
            
            atw = A.T@W

            coeffsSinB = linalg.pinv(atw@A)@atw
            coeffs = coeffsSinB@b
            
            l = x@coeffsSinB

            y_est = np.dot(coeffs, x[0])
            y_ests[i] = y_est

        return y_ests

    def score(self, X, y):
        y_est = self.predict(X)
        n = len(y)
        err = 0
        for i in range(n):
            err += (y_est[i] - y[i])**2

        return 1 / (err/n)

    def get_indexes(self, distances, q):
        mins = []
        for i in range(0, len(distances)):
            if len(mins) >= q:
                if mins[0][0] < -1*distances[i]:
                    heapq.heapreplace(mins, (-1*distances[i], i))
            else:
                heapq.heappush(mins, (-1*distances[i], i))
        
        indexes = []
        max_dist = 0.0
        for (dist, index) in mins:
            indexes.append(index)
            
            if -1*dist > max_dist:
                max_dist = -1*dist
                
        return indexes, max_dist
