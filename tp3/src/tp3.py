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

def normalize(array):
    stds = array.std(axis=0)    
    return (array- array.mean(axis=0))/stds

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

def loess(data, Y, f=0.1, fit='quadratic'):
    n = len(Y)
    q = int(math.floor(f*n))
    data_norm = normalize(data)
    if fit == 'quadratic':
        poly = PolynomialFeatures(2)
    
    y_ests = np.zeros_like(Y)
    
    for i in range(0, len(data_norm)):
        distances = linalg.norm(data_norm - data_norm[i], ord=2, axis=1)
        indexes, max_dist = get_indexes(distances, q)
        W = get_weights(distances[indexes], max_dist)
        b = Y[indexes]
        if fit=='quadratic':
            A = poly.fit_transform(data_norm[indexes])
        else:
            A = np.append(np.ones((len(indexes),1)), data_norm[indexes], axis=1)
            
        At = np.transpose(A)
        try:
            coeffs = linalg.solve(np.dot(At, np.dot(W, A)), np.dot(At, np.dot(W, b)))
        except:
            print('matriz singular')
            print(data_norm[i])
            print(data_norm[indexes])
            print(W)
            coeffs = linalg.solve(np.dot(At, A), np.dot(At, b))
        
        
        if fit=='quadratic':
            y_est = np.dot(poly.fit_transform(data_norm[i].reshape(1, -1)),coeffs)
        else:
            y_est = np.dot(np.append([1.0], data_norm[i]), coeffs)
        
        y_ests[i] = y_est
    
    return y_ests
