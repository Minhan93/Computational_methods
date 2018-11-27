import numpy as np
# def matmult(A, B):
#     rowA = len(A)
#     colB = len(B[0])
#     colA = len(A[0])
#     matrix = [[0 for i in range(colB)] for j in range(rowA)]
#     for i in range(rowA):
#         for j in range(colB):
#             for k in range(colA):
#                 matrix[i][j] += A[i][k] * B[k][j]
#     return matrix


def matmult(A, B):
    rowA = len(A)
    colB = len(B[0])
    colA = len(A[0])
    matrix = np.zeros((rowA, colB))
    for i in range(rowA):
        for j in range(colB):
            for k in range(colA):
                matrix[i][j] += A[i][k] * B[k][j]
    return matrix
