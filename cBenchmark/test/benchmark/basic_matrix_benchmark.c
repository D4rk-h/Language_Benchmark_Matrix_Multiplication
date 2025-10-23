#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#include <psapi.h>

double get_wall_time() {
    LARGE_INTEGER time, freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&time);
    return (double)time.QuadPart / (double)freq.QuadPart;
}

double get_process_mb() {
    PROCESS_MEMORY_COUNTERS memCounter;
    GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof(memCounter));
    return (double)memCounter.WorkingSetSize / (1024.0 * 1024.0);
}

void ensure_directory_exists(const char *path) {
    CreateDirectoryA(path, NULL);
}

#else
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

double get_wall_time() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec + t.tv_usec / 1e6;
}

double get_process_mb() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    #ifdef __APPLE__
    return (double)usage.ru_maxrss / (1024.0 * 1024.0);
    #else
    return (double)usage.ru_maxrss / 1024.0;
    #endif
}

void ensure_directory_exists(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0777);
    }
}
#endif

#include "../../basic_matrix/basic_matrix_multiplier.h"
#define NUM_SIZES 5
int sizes[NUM_SIZES] = {128, 256, 512, 1024};
int runs = 5;

void run_benchmarks(const char *csv_path, double times[][5], double memories[][5]) {
    FILE *csvfile = fopen(csv_path, "w");
    if (!csvfile) {
        printf("Error opening file: %s\n", csv_path);
        exit(1);
    }
    fprintf(csvfile, "MatrixSize,Run,TimeSeconds,RealMemoryMB\n");
    for (int s = 0; s < NUM_SIZES; ++s) {
        int n = sizes[s];
        printf("\nRunning benchmarks for matrix size %dx%d...\n", n, n);
        for (int r = 0; r < runs; ++r) {
            double **A = allocate_matrix(n);
            double **B = allocate_matrix(n);
            double **C = allocate_matrix(n);
            if (!A || !B || !C) {
                printf("Error: Memory allocation failed for size %d\n", n);
                exit(1);
            }
            generate_matrices(A, B, n);
            double mem_before = get_process_mb();
            double start = get_wall_time();
            multiply(A, B, C, n);
            double end = get_wall_time();
            double mem_after = get_process_mb();
            double time_seconds = end - start;
            double real_memory_mb = mem_before > mem_after ? mem_before : mem_after;
            times[s][r] = time_seconds;
            memories[s][r] = real_memory_mb;
            fprintf(csvfile, "%d,%d,%.5f,%.5f\n", n, r+1, time_seconds, real_memory_mb);
            printf("  Run %d/%d: %.5fs, %.5fMB\n", r+1, runs, time_seconds, real_memory_mb);
            free_matrix(A, n);
            free_matrix(B, n);
            free_matrix(C, n);
        }
    }
    fclose(csvfile);
}

void print_average_results(double times[][5], double memories[][5]) {
    printf("\n===== AVERAGE RESULTS =====\n");
    printf("%-10s %-15s %-25s\n", "Size", "Avg Time (s)", "Avg Real Mem (MB)");
    for (int s = 0; s < NUM_SIZES; ++s) {
        double sum_time = 0, sum_mem = 0;
        for (int r = 0; r < runs; ++r) {
            sum_time += times[s][r];
            sum_mem += memories[s][r];
        }
        double avg_time = sum_time / runs;
        double avg_mem = sum_mem / runs;
        printf("%-10d %-15.5f %-25.5f\n", sizes[s], avg_time, avg_mem);
    }
}

int main(int argc, char *argv[]) {
    const char *output_dir = "data/";
    if (argc >= 2) {
        output_dir = argv[1];
    }
    ensure_directory_exists(output_dir);
    char csv_path[512];
    #ifdef _WIN32
    snprintf(csv_path, sizeof(csv_path), "%s\\c_benchmark_results.csv", output_dir);
    #else
    snprintf(csv_path, sizeof(csv_path), "%s/c_benchmark_results.csv", output_dir);
    #endif
    double times[NUM_SIZES][5] = {{0}};
    double memories[NUM_SIZES][5] = {{0}};
    printf("==================================================\n");
    printf("C Matrix Multiplication Benchmark\n");
    printf("==================================================\n");
    printf("Matrix sizes: ");
    for (int i = 0; i < NUM_SIZES; ++i) {
        printf("%d%s", sizes[i], i < NUM_SIZES - 1 ? ", " : "\n");
    }
    printf("Runs per size: %d\n", runs);
    printf("Output directory: %s\n", output_dir);
    run_benchmarks(csv_path, times, memories);
    print_average_results(times, memories);
    printf("\n==================================================\n");
    printf("Benchmark finished. Results saved at: %s\n", csv_path);
    printf("==================================================\n");
    return 0;
}