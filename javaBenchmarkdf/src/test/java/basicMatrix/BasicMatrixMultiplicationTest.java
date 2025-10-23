package basicMatrix;

import org.junit.Before;
import org.junit.Test;
import java.util.List;
import static org.junit.Assert.assertEquals;

public class BasicMatrixMultiplicationTest {
    private double[][] A;
    private double[][] B;
    private double[][] expected;
    private BasicMatrixMultiplier multiplier;

    @Before
    public void setUp() {
        A = new double[][] {{1, 2}, {3, 4}};
        B = new double[][] {{5, 6}, {7, 8}};
        expected = new double[][] {{19, 22}, {43, 50}};
        multiplier = new BasicMatrixMultiplier();
    }

    @Test
    public void testMultiply() {
        double[][] result = multiplier.multiply(A, B);
        assertMatrixEquals(expected, result, 1e-10);
    }

    @Test
    public void testGenerateMatricesCreatesCorrectShape() {
        int n = 5;
        List<double[][]> matrices = multiplier.generateMatrices(n);
        assertEquals(n, matrices.get(0).length);
        assertEquals(n, matrices.get(0)[0].length);
        assertEquals(n, matrices.get(1).length);
        assertEquals(n, matrices.get(1)[0].length);
    }

    @Test
    public void testMultiplyWithRandomMatrices() {
        int n = 3;
        List<double[][]> matrices = multiplier.generateMatrices(n);
        double[][] result = multiplier.multiply(matrices.get(0), matrices.get(1));
        assertEquals(n, result.length);
        assertEquals(n, result[0].length);
    }

    private void assertMatrixEquals(double[][] expected, double[][] actual, double delta) {
        assertEquals(expected.length, actual.length);
        for (int i = 0; i < expected.length; i++) {
            assertEquals(expected[i].length, actual[i].length);
            for (int j = 0; j < expected[i].length; j++) {
                assertEquals(expected[i][j], actual[i][j], delta);
            }
        }
    }
}
