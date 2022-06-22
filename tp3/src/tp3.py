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

def loess(data, Y, f=0.1, fit=1, dist=2, normalize=True):
    cant = len(Y)
    q = int(math.ceil(f*cant))
    if normalize:
        data = normalized(data)
    else:
        data = data
    
    y_ests = np.zeros_like(Y,dtype="float64")
    poly = PolynomialFeatures(fit)
    
    for i in range(0, cant):
        distances = linalg.norm(data - data[i], ord=dist, axis=1)
        indexes, max_dist = get_indexes(distances, q)
        W = get_weights(distances[indexes], max_dist)
        b = Y[indexes]
        A = poly.fit_transform(data[indexes])
            
        At = np.transpose(A)
        try:
            coeffs = linalg.solve(np.dot(At, np.dot(W, A)), np.dot(At, np.dot(W, b)))
        except:

            U, E, Vt = linalg.svd(np.dot(W, A))
            V = np.transpose(Vt)
            Ut = np.transpose(U)
            
            Et = np.zeros((np.shape(V)[1], np.shape(Ut)[0]))
            
            for j in range(0, len(E)):
                if E[j] != 0:
                    Et[j,j] = 1/E[j]
            
            MPInv = np.dot(V, np.dot(Et, Ut))
            coeffs = np.dot(MPInv, np.dot(W, b))
        
        y_est = np.dot(poly.fit_transform(data[i].reshape(1, -1)),coeffs)

        y_ests[i] = y_est
    
    return y_ests
