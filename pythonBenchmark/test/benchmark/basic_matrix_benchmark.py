import sys
import time
import csv
import os
import psutil
from basic_matrix.basic_matrix_multiplier import BasicMatrixMultiplier


sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../..')))

def get_process_memory_mb():
    process = psutil.Process(os.getpid())
    return process.memory_info().rss / (1024 * 1024)

def run_benchmarks(sizes, runs, csv_path):
    times = {}
    real_memories = {}
    with open(csv_path, "w", newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(["MatrixSize", "Run", "TimeSeconds", "RealMemoryMB"])
        for size in sizes:
            times[size] = []
            real_memories[size] = []
            print(f"\nRunning benchmarks for matrix size {size}x{size}...")
            for run in range(1, runs + 1):
                multiplier = BasicMatrixMultiplier()
                A, B = multiplier.generate_matrices(size)
                mem_before = get_process_memory_mb()
                start = time.time()
                result = multiplier.multiply(A, B)
                end = time.time()
                mem_after = get_process_memory_mb()
                time_seconds = round(end - start, 5)
                real_memory_mb = round(max(mem_before, mem_after), 5)
                times[size].append(time_seconds)
                real_memories[size].append(real_memory_mb)
                writer.writerow([size, run, time_seconds, real_memory_mb])
                print(f"  Run {run}/{runs}: {time_seconds}s, {real_memory_mb}MB")
    return times, real_memories

def print_average_results(sizes, times, real_memories):
    print("\n===== AVERAGE RESULTS =====")
    print("{:<10} {:<15} {:<25}".format("Size", "Avg Time (s)", "Avg Real Mem (MB)"))
    for size in sizes:
        avg_time = round(sum(times[size]) / len(times[size]), 5)
        avg_real_mem = round(sum(real_memories[size]) / len(real_memories[size]), 5)
        print("{:<10} {:<15.5f} {:<25.5f}".format(size, avg_time, avg_real_mem))


if __name__ == "__main__":
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.join(script_dir, '../../..')
    output_directory = os.path.join(project_root, 'data')
    sizes = [128, 256, 512, 1024]
    runs = 5
    os.makedirs(output_directory, exist_ok=True)
    csv_path = os.path.join(output_directory, "python_benchmark_results.csv")
    print("=" * 40)
    print("Python Matrix Multiplication Benchmark")
    print("=" * 40)
    print(f"Matrix sizes: {sizes}")
    print(f"Runs per size: {runs}")
    print(f"Output directory: {output_directory}")
    times, real_memories = run_benchmarks(sizes, runs, csv_path)
    print_average_results(sizes, times, real_memories)
    print("\n" + "=" * 40)
    print(f"Benchmark finished. Results saved at: {csv_path}")
    print("=" * 40)