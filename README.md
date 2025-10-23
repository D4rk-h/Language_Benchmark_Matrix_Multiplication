# Language Benchmark: Matrix Multiplication

A comparative benchmark study of matrix multiplication implementations across C, Java, and Python. This project evaluates execution time and memory usage for different matrix sizes.

## Overview

This benchmark implements basic matrix multiplication (naive O(n³) algorithm) in three programming languages to compare their performance characteristics. Results are documented in the accompanying research paper.

## Project Structure

```
├── cBenchmark/           # C implementation
├── javaBenchmarkdf/      # Java implementation
├── pythonBenchmark/      # Python implementation
└── data/                 # Benchmark results (CSV)
```

## Languages & Versions

- **C**: GCC with `-O3` optimization
- **Java**: JDK 9+
- **Python**: Python 3.x with psutil

## Running Benchmarks

### C
```bash
cd cBenchmark
make benchmark
make run_benchmark
```

### Java
```bash
cd javaBenchmarkdf
mvn test
mvn exec:java -Dexec.mainClass="benchmark.BasicMatrixBenchmark"
```

### Python
```bash
cd pythonBenchmark
python test/benchmark/basic_matrix_benchmark.py
```

## Benchmark Configuration

- **Matrix sizes**: 128×128, 256×256, 512×512, 1024×1024
- **Runs per size**: 5
- **Metrics**: Execution time (seconds), Memory usage (MB)

## Results

Results are saved as CSV files in the `data/` directory. Visualization scripts are included in the Python benchmark folder.

To generate plots:
```bash
cd pythonBenchmark
python plot_benchmark.py
```

## Testing

Each implementation includes unit tests:

- **C**: `make run_test`
- **Java**: `mvn test`
- **Python**: `python -m unittest discover`

## Paper

See the accompanying research paper for detailed analysis and conclusions.

