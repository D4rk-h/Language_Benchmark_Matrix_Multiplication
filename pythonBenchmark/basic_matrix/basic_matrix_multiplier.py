import random


class BasicMatrixMultiplier:
    def __init__(self):
        self.random = random.Random()

    def generate_matrices(self, n):
        matrix_a = [[self.random.uniform(0, 100) for _ in range(n)] for _ in range(n)]
        matrix_b = [[self.random.uniform(0, 100) for _ in range(n)] for _ in range(n)]
        return matrix_a, matrix_b

    def multiply(self, m1, m2):
        dim = len(m1)
        result_matrix = [[0.0 for _ in range(dim)] for _ in range(dim)]
        for i in range(dim):
            for j in range(dim):
                for k in range(dim):
                    result_matrix[i][j] += m1[i][k] * m2[k][j]
        return result_matrix