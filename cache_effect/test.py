from random import randint
import numpy as np
import time
from ise407_hw1 import *
N = [16, 32, 64, 128, 256, 512, 768, 1024]
for n in N:
    rowA = n
    colB = n
    colA = n

    # A = [[randint(0, 100) for i in range(colA)] for j in range(rowA)]
    # B = [[randint(0, 100) for i in range(colB)] for j in range(colA)]
    A = np.random.randint(0, 100, (rowA, colA))
    B = np.random.randint(0, 100, (colA, colB))

    begin = time.time()
    C = matmult(A, B)
    end = time.time()
    # print(C)
    print(end - begin)
