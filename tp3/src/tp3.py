import numpy as np
import math
import numpy.linalg as linalg
import pandas as pd
import sklearn as skl
from sklearn.preprocessing import PolynomialFeatures
import heapq

def tricubic(x):
    y = np.zeros_like(x)
    idx = (x >= 0) & (x <= 1)
    y[idx] = np.power(1.0 - np.power(np.abs(x[idx]), 3), 3)
    return y

def normalized(array):
    stds = array.std(axis=0)
    
    return (array- array.mean(axis=0))/stds, (est - array.mean(axis=0))/stds

def get_indexes(distances, q):
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

def get_weights(distances, max_dist):
    weights = tricubic(distances/max_dist)
    return np.diag(weights)

def loess(data, Y, to_estimate, f=0.1, fit=1, dist=2, normalize=True):
    q = int(math.ceil(f*len(Y)))
    if normalize:
        data, to_estimate = normalized(data, to_estimate)
        
    
    poly = PolynomialFeatures(fit)
    cant = len(to_estimate)
    
    y_ests = np.zeros(cant,dtype="float64")
    
    for i in range(cant):
        distances = linalg.norm(data - to_estimate[i], ord=dist, axis=1)
        indexes, max_dist = get_indexes(distances, q)

        A = poly.fit_transform(data[indexes])
        x = poly.transform(to_estimate[i].reshape(1,-1))

        W = get_weights(distances[indexes], max_dist)

        b = Y[indexes]
        
        atw = A.T@W

        coeffsSinB = linalg.pinv(atw@A)@atw
        coeffs = coeffsSinB@b
        
        l = x@coeffsSinB

        y_est = np.dot(coeffs, x[0])
        y_ests[i] = y_est
    
    return y_ests
