package benchmark;

import basicMatrix.BasicMatrixMultiplier;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;


public class BasicMatrixBenchmark {

    public static void main(String[] args) {
        String outputDirectory;
        if (args.length < 1) {
            outputDirectory = "data/";
            System.out.println("No output directory specified. Using default: " + outputDirectory);
        } else {
            outputDirectory = args[0];
        }

        int[] sizes = {128, 256, 512, 1024};
        int runs = 5;

        String csvPath = outputDirectory + "/java_benchmark_results.csv";

        System.out.println("==================================================");
        System.out.println("Java Matrix Multiplication Benchmark");
        System.out.println("==================================================");
        System.out.println("Matrix sizes: " + arrayToString(sizes));
        System.out.println("Runs per size: " + runs);
        System.out.println("Output directory: " + outputDirectory);

        Map<Integer, List<Double>> times = new HashMap<>();
        Map<Integer, List<Double>> realMemories = new HashMap<>();
        runBenchmarks(sizes, runs, times, realMemories, csvPath);
        printAverageResults(sizes, times, realMemories);

        System.out.println("\n==================================================");
        System.out.println("Benchmark finished. Results saved at: " + csvPath);
        System.out.println("==================================================");
    }

    private static String arrayToString(int[] array) {
        StringBuilder sb = new StringBuilder("[");
        for (int i = 0; i < array.length; i++) {
            sb.append(array[i]);
            if (i < array.length - 1) sb.append(", ");
        }
        sb.append("]");
        return sb.toString();
    }

    private static void ensureOutputDirExists(String outputDir) {
        File dir = new File(outputDir);
        if (!dir.exists()) dir.mkdirs();
    }

    private static double getProcessMemoryMB() {
        Runtime runtime = Runtime.getRuntime();
        return (runtime.totalMemory() - runtime.freeMemory()) / (1024.0 * 1024.0);
    }

    private static void runBenchmarks(int[] sizes, int runs, Map<Integer, List<Double>> times, Map<Integer, List<Double>> realMemories, String csvPath) {
        ensureOutputDirExists(new File(csvPath).getParent());
        try (FileWriter writer = new FileWriter(csvPath)) {
            writer.write("MatrixSize,Run,TimeSeconds,RealMemoryMB\n");
            for (int size : sizes) {
                times.put(size, new ArrayList<>());
                realMemories.put(size, new ArrayList<>());
                System.out.println("\nRunning benchmarks for matrix size " + size + "x" + size + "...");

                for (int run = 1; run <= runs; run++) {
                    BasicMatrixMultiplier multiplier = new BasicMatrixMultiplier();
                    List<double[][]> matrices = multiplier.generateMatrices(size);

                    System.gc();
                    double memBefore = getProcessMemoryMB();
                    long start = System.nanoTime();
                    double[][] result = multiplier.multiply(matrices.get(0), matrices.get(1));
                    long end = System.nanoTime();
                    double memAfter = getProcessMemoryMB();

                    double timeSeconds = (end - start) / 1_000_000_000.0;
                    double realMemoryMB = Math.max(memBefore, memAfter);

                    timeSeconds = Math.round(timeSeconds * 100000.0) / 100000.0;
                    realMemoryMB = Math.round(realMemoryMB * 100000.0) / 100000.0;

                    times.get(size).add(timeSeconds);
                    realMemories.get(size).add(realMemoryMB);

                    writer.write(size + "," + run + "," + timeSeconds + "," + realMemoryMB + "\n");
                    System.out.println("  Run " + run + "/" + runs + ": " + timeSeconds + "s, " + realMemoryMB + "MB");
                }
            }
        } catch (IOException e) {
            System.out.println("Error writing benchmark results: " + e.getMessage());
        }
    }

    private static void printAverageResults(int[] sizes, Map<Integer, List<Double>> times, Map<Integer, List<Double>> realMemories) {
        System.out.println("\n===== AVERAGE RESULTS =====");
        System.out.printf("%-10s %-15s %-25s%n", "Size", "Avg Time (s)", "Avg Real Mem (MB)");
        for (int size : sizes) {
            double averageTime = times.get(size).stream().mapToDouble(Double::doubleValue).average().orElse(0.0);
            double averageMemory = realMemories.get(size).stream().mapToDouble(Double::doubleValue).average().orElse(0.0);
            averageTime = Math.round(averageTime * 100000.0) / 100000.0;
            averageMemory = Math.round(averageMemory * 100000.0) / 100000.0;
            System.out.printf("%-10d %-15.5f %-25.5f%n", size, averageTime, averageMemory);
        }
    }
}
