import os
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np


def read_summary(path):
    df = pd.read_csv(path)
    grouped = df.groupby("MatrixSize").agg({"TimeSeconds": "mean", "RealMemoryMB": "mean"}).reset_index()
    return grouped

def plot_execution_time(results):
    plt.figure(figsize=(10, 6))
    for lang, df in results.items():
        plt.plot(df["MatrixSize"], df["TimeSeconds"], marker="o", label=lang, linewidth=2)
    plt.xlabel("Matrix Size (n x n)", fontsize=12)
    plt.ylabel("Average Time (seconds)", fontsize=12)
    plt.title("Matrix Multiplication Benchmark: Execution Time", fontsize=14, fontweight='bold')
    plt.legend(fontsize=10)
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    plt.savefig("benchmark_time.png", dpi=300)
    plt.show()

def plot_memory_usage(results):
    plt.figure(figsize=(10, 6))
    for lang, df in results.items():
        plt.plot(df["MatrixSize"], df["RealMemoryMB"], marker="o", label=lang, linewidth=2)
    plt.xlabel("Matrix Size (n x n)", fontsize=12)
    plt.ylabel("Average Real Memory (MB)", fontsize=12)
    plt.title("Matrix Multiplication Benchmark: Memory Usage", fontsize=14, fontweight='bold')
    plt.legend(fontsize=10)
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    plt.savefig("benchmark_memory.png", dpi=300)
    plt.show()

def plot_execution_time_bar(results):
    plt.figure(figsize=(12, 6))
    matrix_sizes = list(results.values())[0]["MatrixSize"].values
    num_sizes = len(matrix_sizes)
    n_lang = len(results)
    x = np.arange(num_sizes)
    width = 0.8 / n_lang
    for i, (lang, df) in enumerate(results.items()):
        offset = width * i - (width * (num_langs - 1) / 2)
        plt.bar(x + offset, df["TimeSeconds"], width, label=lang, alpha=0.8)
    plt.xlabel("Matrix Size (n x n)", fontsize=12)
    plt.yscale('log')
    plt.ylabel("Average Time (seconds)", fontsize=12)
    plt.title("Matrix Multiplication Benchmark: Execution Time (Bar Chart)", fontsize=14, fontweight='bold')
    plt.xticks(x, matrix_sizes)
    plt.legend(fontsize=10)
    plt.grid(True, alpha=0.3, axis='y')
    plt.tight_layout()
    plt.savefig("benchmark_time_bar.png", dpi=300)
    plt.show()

def plot_memory_usage_bar(results):
    plt.figure(figsize=(12, 6))
    matrix_sizes = list(results.values())[0]["MatrixSize"].values
    num_sizes = len(matrix_sizes)
    num_langs = len(results)
    x = np.arange(num_sizes)
    width = 0.8 / num_langs
    for i, (lang, df) in enumerate(results.items()):
        offset = width * i - (width * (num_langs - 1) / 2)
        plt.bar(x + offset, df["RealMemoryMB"], width, label=lang, alpha=0.8)
    plt.xlabel("Matrix Size (n x n)", fontsize=12)
    plt.ylabel("Average Real Memory (MB)", fontsize=12)
    plt.title("Matrix Multiplication Benchmark: Memory Usage (Bar Chart)", fontsize=14, fontweight='bold')
    plt.xticks(x, matrix_sizes)
    plt.legend(fontsize=10)
    plt.grid(True, alpha=0.3, axis='y')
    plt.tight_layout()
    plt.savefig("benchmark_memory_bar.png", dpi=300)
    plt.show()

def main():
    folder = "data/"
    files = {
        "C": os.path.join(folder, "c_benchmark_results.csv"),
        "Python": os.path.join(folder, "python_benchmark_results.csv"),
        "Java": os.path.join(folder, "java_benchmark_results.csv"),
    }
    results = {}
    for lang, file in files.items():
        if os.path.exists(file):
            results[lang] = read_summary(file)
            print(f"Loaded data for {lang}")
        else:
            print(f"Warning: File not found: {file}")
    if not results:
        print("Error: No benchmark data files found!")
        return
    plot_execution_time(results)
    plot_memory_usage(results)
    plot_execution_time_bar(results)
    plot_memory_usage_bar(results)
    print("Plots saved")


if __name__ == "__main__":
    main()