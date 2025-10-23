package basicMatrix;

import java.util.List;
import java.util.Random;

public class BasicMatrixMultiplier {
    private final Random random;

    public BasicMatrixMultiplier() {this.random = new Random();}

    public double[][] multiply(double[][] m1, double[][] m2) {
        int dim = m1.length;
        double[][] resultMatrix = new double[dim][dim];
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                for (int k = 0; k < dim; k++) {
                    resultMatrix[i][j] += m1[i][k] * m2[k][j];
                }
            }
        }
        return resultMatrix;
    }

    public List<double[][]> generateMatrices(int n) {
        double[][] A = new double[n][n];
        double[][] B = new double[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = random.nextDouble();
                B[i][j] = random.nextDouble();
            }
        }
        return List.of(A, B);
    }
}
