CC = gcc
CFLAGS = -O3 -march=native -lm -Wall
WINFLAGS = -O3 -march=native -lpsapi -Wall

OUTPUT_DIR_UNIX = data/output
OUTPUT_DIR_WIN = data\output

ifeq ($(OS),Windows_NT)
    EXE = .exe
    WIN = 1
    MKDIR = if not exist $(OUTPUT_DIR_WIN) mkdir $(OUTPUT_DIR_WIN)
    OUTPUT_DIR = $(OUTPUT_DIR_WIN)
    RM = del /Q
else
    EXE =
    WIN = 0
    MKDIR = mkdir -p $(OUTPUT_DIR_UNIX)
    OUTPUT_DIR = $(OUTPUT_DIR_UNIX)
    RM = rm -f
endif

.PHONY: all test benchmark run_test run_benchmark clean

all: test benchmark

test: test/basic_matrix_test/basic_matrix_multiplier_test.c basic_matrix/basic_matrix_multiplier.c basic_matrix/basic_matrix_multiplier.h
	$(CC) test/basic_matrix_test/basic_matrix_multiplier_test.c basic_matrix/basic_matrix_multiplier.c -o test_matrix$(EXE) $(CFLAGS)

benchmark: test/benchmark/basic_matrix_benchmark.c basic_matrix/basic_matrix_multiplier.c basic_matrix/basic_matrix_multiplier.h
ifeq ($(WIN),1)
	$(CC) test/benchmark/basic_matrix_benchmark.c basic_matrix/basic_matrix_multiplier.c -o benchmark$(EXE) $(WINFLAGS)
else
	$(CC) test/benchmark/basic_matrix_benchmark.c basic_matrix/basic_matrix_multiplier.c -o benchmark$(EXE) $(CFLAGS)
endif

run_test: test
	./test_matrix$(EXE)

run_benchmark: benchmark
	$(MKDIR)
	./benchmark$(EXE) $(OUTPUT_DIR)

clean:
ifeq ($(WIN),1)
	$(RM) test_matrix$(EXE) benchmark$(EXE)
else
	$(RM) test_matrix$(EXE) benchmark$(EXE)
endif