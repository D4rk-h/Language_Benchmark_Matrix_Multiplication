import unittest
from basic_matrix.basic_matrix_multiplier import BasicMatrixMultiplier

class BasicMatrixMultiplierTest(unittest.TestCase):

    def setUp(self):
        self.A = [[1, 2], [3, 4]]
        self.B = [[5, 6], [7, 8]]
        self.expected = [[19, 22], [43, 50]]
        self.multiplier = BasicMatrixMultiplier()

    def test_multiply(self):
        result = self.multiplier.multiply(self.A, self.B)
        self.assert_matrix_almost_equal(self.expected, result, delta=1e-10)

    def test_generate_matrices_shape(self):
        n = 3
        A, B = self.multiplier.generate_matrices(n)
        self.assertEqual(len(A), n)
        self.assertEqual(len(A[0]), n)
        self.assertEqual(len(B), n)
        self.assertEqual(len(B[0]), n)

    def test_multiply_with_random_matrices(self):
        n = 4
        A, B = self.multiplier.generate_matrices(n)
        result = self.multiplier.multiply(A, B)
        self.assertEqual(len(result), n)
        self.assertEqual(len(result[0]), n)

    def assert_matrix_almost_equal(self, expected, actual, delta):
        self.assertEqual(len(expected), len(actual))
        for i in range(len(expected)):
            self.assertEqual(len(expected[i]), len(actual[i]))
            for j in range(len(expected[i])):
                self.assertAlmostEqual(expected[i][j], actual[i][j], delta=delta)

if __name__ == '__main__':
    unittest.main()