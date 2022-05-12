import sys
sys.path.append('build\Debug')

import mnpy as mn
import numpy as np

B = np.array([ [5, 0, 0], [0, 4, 0], [0, 0, 3]])
x0 = np.array([1, 1, 1])
eigenvalue = mn.powerIteration(B, x0, 120, 0.0001)
print(eigenvalue)

