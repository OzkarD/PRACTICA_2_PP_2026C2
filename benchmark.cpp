#include <stdio.h>
#include <chrono>
#include <omp.h>
#include "benchmark.h"
#include "matrix_tools.h"

TimingResult benchmarkMatMul(MatMulFn fn, const Matrix* A, const Matrix* B, Matrix* C, const Matrix* reference, int modN, int repetitions)
{
    TimingResult best = { 1e100, 1e100, 0 };
    for (int r = 0; r < repetitions; r++) 
    {
        auto c0 = std::chrono::high_resolution_clock::now();
        double o0 = omp_get_wtime();
        fn(A, B, C, modN);
        double o1 = omp_get_wtime();
        auto c1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = c1 - c0;
        if (elapsed.count() < best.chronoSeconds) 
        {
            best.chronoSeconds = elapsed.count();
            best.ompSeconds = o1 - o0;
            best.correct = matricesEqual(C, reference);
        }
    }
    return best;
}

TimingResult benchmarkMatMulBlocked(MatMulBlockedFn fn, const Matrix* A, const Matrix* B, Matrix* C, const Matrix* reference, int modN, int blockSize, int repetitions)
{
    TimingResult best = { 1e100, 1e100, 0 };
    for (int r = 0; r < repetitions; r++) {
        auto c0 = std::chrono::high_resolution_clock::now();
        double o0 = omp_get_wtime();
        fn(A, B, C, modN, blockSize);
        double o1 = omp_get_wtime();
        auto c1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = c1 - c0;
        if (elapsed.count() < best.chronoSeconds) {
            best.chronoSeconds = elapsed.count();
            best.ompSeconds = o1 - o0;
            best.correct = matricesEqual(C, reference);
        }
    }
    return best;
}

void printBenchmarkTable(const TimingResult* seq, const TimingResult* ompRows, const TimingResult* ompCollapse, const TimingResult* ompTranspose, const TimingResult* ompBlocked)
{
    printf("\n%-32s %-15s %-15s %-10s %-10s\n", "Metodo", "chrono(s)", "omp(s)", "Speedup", "Correcto");
    printf("--------------------------------------------------------------------------------\n");
    printf("%-32s %-15.6f %-15.6f %-10.3f %-10s\n", "Secuencial", seq->chronoSeconds, seq->ompSeconds, 1.0, seq->correct ? "SI" : "NO");
    printf("%-32s %-15.6f %-15.6f %-10.3f %-10s\n", "OMP parallel for filas", ompRows->chronoSeconds, ompRows->ompSeconds, seq->chronoSeconds / ompRows->chronoSeconds, ompRows->correct ? "SI" : "NO");
    printf("%-32s %-15.6f %-15.6f %-10.3f %-10s\n", "OMP collapse(2)", ompCollapse->chronoSeconds, ompCollapse->ompSeconds, seq->chronoSeconds / ompCollapse->chronoSeconds, ompCollapse->correct ? "SI" : "NO");
    printf("%-32s %-15.6f %-15.6f %-10.3f %-10s\n", "OMP B transpuesta", ompTranspose->chronoSeconds, ompTranspose->ompSeconds, seq->chronoSeconds / ompTranspose->chronoSeconds, ompTranspose->correct ? "SI" : "NO");
    printf("%-32s %-15.6f %-15.6f %-10.3f %-10s\n", "OMP blocked/tiling", ompBlocked->chronoSeconds, ompBlocked->ompSeconds, seq->chronoSeconds / ompBlocked->chronoSeconds, ompBlocked->correct ? "SI" : "NO");
}
